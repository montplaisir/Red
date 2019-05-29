
#ifndef __RED_MGR__
#define __RED_MGR__

#include <memory>
#include "Red.hpp"

// Manager for Evaluator
class RedMgr
{
private:
    std::unique_ptr<Red> _red;

public:
    explicit RedMgr(std::unique_ptr<Red> red)
      : _red(std::move(red))
    {};

    virtual ~RedMgr() {};

    // Set up parallelism and launch run()
    bool runAll(bool &stop) const;

private:
    // Run for all threads
    bool run(bool &stop) const;
};

#endif // __RED_MGR__
