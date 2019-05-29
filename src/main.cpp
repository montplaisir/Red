#include <iostream> 
#include "RedMgr.hpp"

int main()   
{  
    bool stop = false;
    bool overallSuccess = false;

    auto red = std::make_unique<Red>();
    RedMgr redmgr(std::move(red));

    overallSuccess = redmgr.runAll(stop);
    std::cout << "Success: " << overallSuccess << std::endl;
}
