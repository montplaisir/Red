#include <iostream> 
#include "RedMgr.hpp"

int main(int argc, char ** argv)
{  
    bool stop = false;
    bool overallSuccess = false;

    auto red = std::make_unique<Red>();
    int numThreads = 4;
    if (argc > 1)
    {
        numThreads = std::atoi(argv[1]);
    }
    std::cout << "Using " << numThreads << " threads." << std::endl;
    RedMgr redmgr(std::move(red), numThreads);

    overallSuccess = redmgr.runAll(stop);
    std::cout << "Success: " << overallSuccess << std::endl;
}
