import PyRed
import random
import sys
import threading

# This example of blackbox function is for a single process
# The blackbox output must be put in the EvalPoint passed as argument
def bb():
    print("        VRM: Correctly in bb()")
    rnd = random.randint(1, 4)
    eval = (0 == rnd % 3)
    print("        In bb(), rnd is " + str(rnd) + ", eval is " + str(eval))
    return eval


numThreads = 4
if (len(sys.argv) > 1):
    numThreads = int(sys.argv[1])

print("Calling red on " + str(numThreads) + " threads")
success = PyRed.optimize(bb, numThreads)
print("Red returns: " + str(success))
