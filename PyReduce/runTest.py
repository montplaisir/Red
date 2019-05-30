import PyReduce
import sys
import threading

# This example of blackbox function is for a single process
# The blackbox output must be put in the EvalPoint passed as argument
def bb(x):
    print("VRM: in bb(x)")
    # Get thread num. This is the Python thread number, which is
    # different than the OpenMP thread number.
    threadNum = threading.get_ident()
    eval = (0 == threadNum % 3)
    print("In bb(x), thread number is " + str(threadNum) + " eval is " + str(eval))
    return eval


numThreads = 4
if (len(sys.argv) > 1):
    numThreads = int(sys.argv[1])

print("Calling reduce on " + str(numThreads) + " threads")
success = PyReduce.optimize(bb, numThreads)
print("Reduce returns: " + str(success))
