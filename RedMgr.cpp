#include <iostream>  
#include <omp.h>  
#include <unistd.h> // For usleep

#include "RedMgr.hpp"
  
bool RedMgr::run(bool &stop) const
{
    // I want success to be global to all threads.
    bool success = false;
    int threadNum = omp_get_thread_num();
    if (!stop)
    {
        // newSuccess is local to threads.
        usleep(100000);
        bool newSuccess = _red.eval(threadNum);
        #pragma omp critical(updateSuccessType)
        {
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
    return success;
}

