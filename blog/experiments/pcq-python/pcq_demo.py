import os
from multiprocessing import *
# from multiprocessing.dummy import * # switch to thread mode

# Step 2: Defines the produce() and consume() functions
def produce(q, done):
    for x in xrange(100):
        print "producing: " + str(x) 
        q.put(x)
    done.value = 1
    
def consume(x):
    print "process id: " + str(os.getpid()) + " is consuming: " + str(x)
    


if __name__ == '__main__':
    # Step 1: Prepare the data structures
    
    # You have to use data structure from Manager() so 
    # they can be shared across all processes, multiprocessing.Queue
    # only works between parent and child process
    mgr = Manager()
    queue = mgr.Queue()
    done = mgr.Value('i', 0) # indicate if the producer has done producing
    
    # Step 2: Defines the produce() and consume() functions
    # See above
        
    # Step 3: Orchestrate the threads/process
    p = Process(target=produce, args=(queue, done))
    p.start()
    
    c = Pool(processes = 4)
    while not (done.value == 1 and queue.empty()):
        x = queue.get()
        c.apply_async(consume, (x,))

    c.close()
    c.join()
    p.join()

     