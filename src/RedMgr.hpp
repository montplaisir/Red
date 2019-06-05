
#ifndef __RED_MGR__
#define __RED_MGR__

#include <iostream> 
#include <memory>
#include <omp.h>

// Evaluator
class Evaluator
{
    public:
    Evaluator() {};

    virtual ~Evaluator() {};

    // This is the eval function that will be run in parallel.
    // In Cython, it will be a callback.
    virtual bool eval() const
    {
        std::cout << "In Red::eval. Should not get here if bb is set!" << std::endl;
        bool ret = (1 == omp_get_thread_num());
        std::cout << "Red::eval: return " << ret << std::endl;
        return ret;
    }

};

// Manager for Evaluator
class RedMgr
{
private:
    std::unique_ptr<Evaluator> _evaluator;
    int _numThreads;

public:
    explicit RedMgr(std::unique_ptr<Evaluator> evaluator, const int numThreads)
      : _evaluator(std::move(evaluator)),
        _numThreads(numThreads)
    {};

    virtual ~RedMgr() {};

    // Set up parallelism and launch eval on all threads
    bool run() const
    {
        omp_set_num_threads(_numThreads);
        bool retValue = false;
        #pragma omp parallel shared(retValue)
        {
            retValue = _evaluator->eval();
        }
        // For amusement. retValue will vary depending on the order in which the
        // threads are evaluated.
        return retValue;
    }


};

#endif // __RED_MGR__
