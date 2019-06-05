# PyRed: Integration of Red in Python

# Cython compiler directives
#cython: language_level=3
#cython: boundscheck=False, wraparound=False, nonecheck=False

from libcpp cimport bool
import threading


# Define the interface function to perform optimization          
def optimize(f, numThreads):
    cdef bool runStatus
    
    print("VRM: optimize: Call runRed with f = " + str(f))
    runStatus = runRed(cb, <void*> f, numThreads)
    print("VRM: optimize: runRed done. returned:")
    print(runStatus)
    return runStatus


cdef extern from "redCyInterface.cpp":
    ctypedef bool (*Callback)(void* apply)
    bool runRed(Callback cb, void* apply, const int numThreads) except+


# Define callback function ---> link with Python     
cdef bool cb(void *f):
    print("    VRM: In cb: Calling f")
    ret = (<object>f)()
    print("    VRM: In cb: f returns " + str(ret))
    return ret

