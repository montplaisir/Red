
#ifndef __RED_MGR__
#define __RED_MGR__

#include "Red.hpp"

// Manager for Evaluator
class RedMgr
{
private:
    Red _red;

    public:
    explicit RedMgr(Red red)
      : _red(red)
    {};

    virtual ~RedMgr() {};

    bool run(bool &stop) const;
};

#endif // __RED_MGR__
