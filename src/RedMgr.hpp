
#ifndef __RED_MGR__
#define __RED_MGR__

#include <memory>
#include "Red.hpp"

// Manager for Evaluator
class RedMgr
{
private:
    std::unique_ptr<Red> _red;
    int _numThreads;

public:
    explicit RedMgr(std::unique_ptr<Red> red, const int numThreads)
      : _red(std::move(red)),
        _numThreads(numThreads)
    {};

    virtual ~RedMgr() {};

    // Set up parallelism and launch run()
    bool runAll(bool &stop) const;

private:
    // Run for all threads
    bool run(bool &stop) const;
};

#endif // __RED_MGR__
