#include <iostream>  
#include <omp.h>  
#include <unistd.h> // For usleep

#include "RedMgr.hpp"
  
bool RedMgr::run(bool &stop) const
{
    // I want success to be global to all threads.
    bool success = false;
    int threadNum = omp_get_thread_num();
    //if (!stop)
    {
        // newSuccess is local to threads.
        usleep(100000);
        bool newSuccess = _red->eval(threadNum);
        #pragma omp critical(updateSuccessType)
        {
            std::cout << "VRM: Update success for thread " << omp_get_thread_num() << std::endl;
            if (newSuccess > success)
            {
                success = newSuccess;
                stop = true;
            }
        }
        #pragma omp critical(writeout)
        {
            std::cout << "Thread: " << threadNum << " success: " << success << " newSuccess: " << newSuccess << std::endl;  
        }
    }
    std::cout << "VRM: Return from RedMgr::run with value " << success << std::endl;
    return success;
}

bool RedMgr::runAll(bool &stop) const
{  
    omp_set_num_threads(_numThreads);  
    bool overallSuccess = false;
    #pragma omp parallel reduction(max: overallSuccess)
    {
        std::cout << "VRM: RedMgr: Call OpenMP thread for run on thread " << omp_get_thread_num() << std::endl;
        overallSuccess = this->run(stop);
        std::cout << "VRM: RedMgr: Done calling OpenMP thread for run on thread " << omp_get_thread_num() << std::endl;
    }
    stop = true;

    return overallSuccess;
}
