import PyReduce
import random
import sys
import threading

# This example of blackbox function is for a single process
# The blackbox output must be put in the EvalPoint passed as argument
def bb(x):
    print("        VRM: in bb(x)")
    rnd = random.randint(1, 4)
    eval = (0 == rnd % 3)
    print("        In bb(x), rnd is " + str(rnd) + ", eval is " + str(eval))
    return eval


numThreads = 4
if (len(sys.argv) > 1):
    numThreads = int(sys.argv[1])

print("Calling reduce on " + str(numThreads) + " threads")
success = PyReduce.optimize(bb, numThreads)
print("Reduce returns: " + str(success))
