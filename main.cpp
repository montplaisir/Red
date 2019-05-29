#include <iostream>  
#include <omp.h>  
#include <unistd.h> // For usleep
  
// Repro the current behavior of the var success in EvaluatorControl::run().
// We want success to keep its highest value. The difficulty is that success
// is a local variable to run.
// So we might want to use omp reduction, omp lastprivate, or other feature.

// This is the eval function that will be run in parallel.
// In Cython, it will be a callback.
bool eval()
{
    return (1 == omp_get_thread_num());
}


bool run(bool &stop)
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


int main()   
{  
    omp_set_num_threads(4);  
    bool stop = false;
    bool overallSuccess = false;
    #pragma omp parallel reduction(max: overallSuccess)
    {
        overallSuccess = run(stop);
    }
    std::cout << "Success: " << overallSuccess << std::endl;
}
