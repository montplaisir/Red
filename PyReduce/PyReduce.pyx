# PyReduce: Integration of Reduce in Python

# Cython compiler directives
#cython: language_level=3
#cython: boundscheck=False, wraparound=False, nonecheck=False

from libcpp cimport bool


# Define the interface function to perform optimization          
def optimize(f, numThreads, nogil=True):
    cdef int runStatus
    
    #print("VRM: optimize: Call runReduce")
    runStatus = runReduce(cb, <void*> f, numThreads)
    #print("VRM: optimize: runReduce done. returned:")
    #print(runStatus)
    return runStatus


cdef extern from "Red.hpp" nogil:
    cdef cppclass Red:
        bool run(bool &stop) nogil
        #bool eval() nogil


cdef class PyReduceRed:
    cdef Red *c_r
    #def run(self, bool stop):
    #    return self.c_r.run(stop)


cdef extern from "reduceCyInterface.cpp" nogil:
    ctypedef int (*Callback)(void* apply, const int i)
    int runReduce(Callback cb, void* apply, const int numThreads) except+


# Define callback function ---> link with Python     
cdef int cb(void *f, const int i) nogil:
    #print("VRM: Calling callback cb")
    #ev = (<object>f)(i)
    #print("VRM: Return " + str(ev))
    #return ev
    return 2

