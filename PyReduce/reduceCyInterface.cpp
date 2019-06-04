
// Author: Viviane Rochon Montplaisir
// Date: May 2019

#include <exception> 
#include <iostream> 
#include <Python.h>
#include <mutex>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "RedMgr.hpp"

typedef int (*Callback)(void* apply, const int i);
static std::mutex   gMutex;

class PyLockGIL
{
private:
    PyGILState_STATE _gilState;

public:
    PyLockGIL()
    {
        std::cout << "    VRM: Lock the GIL" << std::endl;
        std::unique_lock<std::mutex>pyLockLock(gMutex);
        std::cout << "    VRM: Mutex acquired to Lock the GIL" << std::endl;
        _gilState = PyGILState_Ensure();
        std::cout << "    VRM: GIL is locked" << std::endl;
    }
    ~PyLockGIL()
    {
        std::cout << "    VRM: Release the GIL" << std::endl;
        std::unique_lock<std::mutex>pyLockLock(gMutex);
        std::cout << "    VRM: Mutex acquired to Release the GIL" << std::endl;
        PyGILState_Release(_gilState);
        std::cout << "    VRM: GIL released" << std::endl;
    }

    PyLockGIL(const PyLockGIL&) = delete;
    PyLockGIL& operator=(const PyLockGIL&) = delete;

};


//Python Evaluator Class
class PyEval : public Red
{
private:
    Callback    _cb;
    void*       _apply;

public:
    // Constructor
    PyEval(Callback cb,
           void * apply)
      : Red(),
        _cb(cb),
        _apply(apply)
    {
        std::cout << "VRM: Constructor for PyEval" << std::endl;
    }

    PyEval(const PyEval& pyEval) = delete;
    PyEval& operator=(const PyEval& pyEval) = delete;

    //Destructor
    ~PyEval()
    {
        std::cout << "VRM: Destructor for PyEval" << std::endl;
    }

    bool eval(const int i) const override
    {
        int success = 0;

        //Call Python function on a single EvalPoint
        try
        {
            PyLockGIL pyLockGIL;
            std::cout << "    VRM: Call _cb(_apply, " << i << ")" << std::endl;
            success = _cb(_apply, i);
            std::cout << "    VRM: _cb returned " << success << std::endl;
            if (-1 == success)
            {
                std::cout << "Unrecoverable Error from Callback. Exiting" << std::endl;
                //Force exit
                raise(SIGINT);
                return false;
            }
        }
        //If these errors occur, it is due to errors in python code
        catch(...)
        {
            std::cout << "Unrecoverable Error from Callback. Exiting" << std::endl;
            //Force exit
            raise(SIGINT);
            return false;
        }

        std::cout << "    VRM: eval returns " << (1 == success) << std::endl;
        if (1 == success)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};


static int runReduce(Callback cb,
                     void* apply,
                     const int numThreads)
{
    int overallSuccess = 0;

    try
    {
        std::unique_ptr<Red> pyEval = std::make_unique<PyEval>(cb, apply);

        RedMgr redmgr(std::move(pyEval), numThreads);

        bool stop = false;
        std::cout << "VRM: Call RedMgr::runAll()" << std::endl;
        overallSuccess = (int)redmgr.runAll(stop);
        std::cout << "VRM: Call to RedMgr::runAll() done." << std::endl;

    }

    catch(std::exception &e)
    {
        printf("Reduce exception:\n%s\n",e.what());
    }

    return overallSuccess;


}
