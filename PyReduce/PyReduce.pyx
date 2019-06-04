# PyReduce: Integration of Reduce in Python

# Cython compiler directives
#cython: language_level=3
#cython: boundscheck=False, wraparound=False, nonecheck=False

from libcpp cimport bool
import threading


# Define the interface function to perform optimization          
#def optimize(f, numThreads, nogil=True):
def optimize(f, numThreads):
    cdef int runStatus
    
    #Py_Initialize()
    # VRM I think I have to enforce nogil here so that the gil is
    # forcefully released. But I have to fix the compilation, maybe
    # modify runReduce.
    #with nogil:
    print("VRM: optimize: Call runReduce with f = " + str(f))
    runStatus = runReduce(cb, <void*> f, numThreads)
    print("VRM: optimize: runReduce done. returned:")
    print(runStatus)
    return runStatus


cdef extern from "reduceCyInterface.cpp":
    ctypedef int (*Callback)(void* apply, const int i)
    int runReduce(Callback cb, void* apply, const int numThreads) except+


# Define callback function ---> link with Python     
#cdef int cb(void *f, const int i) nogil:
cdef int cb(void *f, const int i):
    # VRM: Problem here:
    # - If we want to use a Python object, we need the gil. Otherwise, the compilation fails.
    # - If we do use the gil, it blocks the calls to f.
    #with gil:
    print("    VRM: In cb: Calling f")
    ret = (<object>f)(i)
    print("    VRM: In cb: f returns " + str(ret))
    return ret

