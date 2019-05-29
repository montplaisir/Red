#include <iostream> 
#include <omp.h>  
#include "Red.hpp"

int main()   
{  
    omp_set_num_threads(4);  
    bool stop = false;
    bool overallSuccess = false;
    Red red;
    #pragma omp parallel reduction(max: overallSuccess)
    {
        overallSuccess = red.run(stop);
    }
    std::cout << "Success: " << overallSuccess << std::endl;
}
