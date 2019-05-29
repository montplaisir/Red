#include <iostream> 
#include <omp.h>  
#include "RedMgr.hpp"

int main()   
{  
    omp_set_num_threads(4);  
    bool stop = false;
    bool overallSuccess = false;
    Red red;
    RedMgr redmgr(red);
    #pragma omp parallel reduction(max: overallSuccess)
    {
        overallSuccess = redmgr.run(stop);
    }
    std::cout << "Success: " << overallSuccess << std::endl;
}
