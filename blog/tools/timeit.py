import sys
import time
import subprocess

start = time.clock()
real_cmd = sys.argv[1:]
subprocess.check_call(real_cmd, shell=True)
print "Elapsed Time: %f" % (time.clock() - start)

