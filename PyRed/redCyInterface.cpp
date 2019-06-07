
// Author: Viviane Rochon Montplaisir
// Date: May 2019

#include <iostream> 
#include <Python.h>
#include <stdio.h>
#include <string.h>

#include "RedMgr.hpp"

typedef bool (*Callback)(void* apply);

class PyLockGIL
{
private:
    PyGILState_STATE _gilState;

public:
    PyLockGIL()
    {
        std::cout << "    VRM: Lock the GIL" << std::endl;
        _gilState = PyGILState_Ensure();
        std::cout << "    VRM: GIL is locked" << std::endl;
    }
    ~PyLockGIL()
    {
        std::cout << "    VRM: Release the GIL" << std::endl;
        PyGILState_Release(_gilState);
        std::cout << "    VRM: GIL released" << std::endl;
    }

    PyLockGIL(const PyLockGIL&) = delete;
    PyLockGIL& operator=(const PyLockGIL&) = delete;

};


//Python Evaluator Class
class PyEval : public Evaluator
{
private:
    Callback    _cb;
    void*       _apply;

public:
    // Constructor
    PyEval(Callback cb,
           void * apply)
      : Evaluator(),
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

    bool eval() const override
    {
        PyLockGIL pyLockGIL;
        std::cout << "    VRM: Calling _cb(_apply)" << std::endl;
        bool success = _cb(_apply);
        std::cout << "    VRM: _cb returned " << success << std::endl;

        return success;
    }

};


static bool runRed(Callback cb,
                   void* apply,
                   const int numThreads)
{
    bool success = 0;

    Py_BEGIN_ALLOW_THREADS
    std::unique_ptr<Evaluator> pyEval = std::make_unique<PyEval>(cb, apply);
    RedMgr redmgr(std::move(pyEval), numThreads);

    std::cout << "VRM: Call RedMgr::run()" << std::endl;
    success = redmgr.run();
    std::cout << "VRM: Call to RedMgr::run() done." << std::endl;
    Py_END_ALLOW_THREADS

    return success;


}
