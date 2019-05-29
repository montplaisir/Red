import PyReduce

# This example of blackbox function is for a single process
# The blackbox output must be put in the EvalPoint passed as argument
def bb(x):
    print("VRM: in bb(x)")
    # Get thread num
    #thread_num = openmp.omp_get_thread_num()
    return 1 # 1: success 0: failed evaluation

success = PyReduce.optimize(bb)
print("Reduce returns: " + str(success))
