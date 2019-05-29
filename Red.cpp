#include <iostream>  
#include <omp.h>  
#include <unistd.h> // For usleep

#include "Red.hpp"
  
// This is the eval function that will be run in parallel.
// In Cython, it will be a callback.
bool Red::eval()
{
    return (1 == omp_get_thread_num());
}


bool Red::run(bool &stop)
{
    // I want success to be global to all threads.
    bool success = false;
    if (!stop)
    {
        // newSuccess is local to threads.
        usleep(100000);
        bool newSuccess = eval();
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
            std::cout << "Thread: " << omp_get_thread_num() << " success: " << success << " newSuccess: " << newSuccess << std::endl;  
        }
    }
    return success;
}

