# PyReduce: Integration of Reduce in Python

#cython: language_level=3

from libcpp cimport bool


# Define the interface function to perform optimization          
def optimize(f, numThreads):
    cdef int runStatus
    
    print("VRM: optimize: Call runReduce")
    runStatus = runReduce(cb, <void*> f, numThreads)
    print("VRM: optimize: runReduce done. returned:")
    print(runStatus)
    return runStatus


cdef extern from "Red.hpp":
    cdef cppclass Red:
        bool run(bool &stop)
        #bool eval();


cdef class PyReduceRed:
    cdef Red *c_r
    #def run(self, bool stop):
    #    return self.c_r.run(stop)


cdef extern from "reduceCyInterface.cpp":
    ctypedef int (*Callback)(void* apply, const int i)
    int runReduce(Callback cb, void* apply, const int numThreads) except+


# Define callback function ---> link with Python     
cdef int cb(void *f, const int i) with gil:
    print("VRM: Calling callback cb")
    #thread = threading.Thread(target=f, args=(u,))
    #ret = thread.start()
    return (<object>f)(i)
    #return ret

