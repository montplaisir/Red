#include <iostream>  
#include <omp.h>  
#include <unistd.h> // For usleep

#include "Red.hpp"
  
// This is the eval function that will be run in parallel.
// In Cython, it will be a callback.
bool Red::eval(const int threadNum) const
{
    std::cout << "VRM: In Red::eval. Should not get here if bb is set!" << std::endl;
    return (1 == threadNum);
}


