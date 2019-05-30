
// Author: Viviane Rochon Montplaisir
// Date: May 2019

#include <exception> 
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "RedMgr.hpp"

typedef int (*Callback)(void* apply, const int i);


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
    }

    //Destructor
    ~PyEval() {}

    bool eval(const int i) const override
    {
        int success = 0;

        //Call Python function on a single EvalPoint
        try
        {
            success = _cb(_apply, i);
            if (-1 == success)
            {
                printf("Unrecoverable Error from Callback, Exiting...\n\n");
                //Force exit
                raise(SIGINT);
                return false;
            }
        }
        //If these errors occur, it is due to errors in python code
        catch(...)
        {
            printf("Unrecoverable Error from Callback, Exiting...\n\n");
            //Force exit
            raise(SIGINT);
            return false;
        }
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
                     int numThreads)
{
    int overallSuccess = 0;

    try
    {
        std::unique_ptr<Red> pyEval = std::make_unique<PyEval>(cb, apply);

        RedMgr redmgr(std::move(pyEval), numThreads);

        bool stop = false;
        overallSuccess = (int)redmgr.runAll(stop);

    }

    catch(std::exception &e)
    {
        printf("Reduce exception:\n%s\n",e.what());
    }

    return overallSuccess;


}
