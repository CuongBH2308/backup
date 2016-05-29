# C++ have RAII (release resource in destructor), and java have try-catch-finally
# but python have both"
# 	1. try-except-finally
# 	2. with statement
# with would be better as you don't have to remember release resource explicitly
# For context manager, there are actually too concepts
# 	1. Context mangaer
#	2. Working Object
# For File object, it is the both, but you can also design you class
# as separated


# use file with 'with'
with open(__file__) as f:
	print f.readline()
print f.closed


# The Working Object
import hashlib
class SecureLog:
	def __init__(self, someFile, marker="-------HASH---------"):
		self.theFile = someFile
		self.marker = marker
		self.hash = hashlib.md5()

	def write(self, aLine):
		self.theFile.write(aLine)
		self.hash.update(aLine)

	def close(self):
		self.theFile.write("\n%s\n%s\n" % (self.marker, self.hash.hexdigest()))
		self.theFile.close()

# The Context manager
class SecureLogManager:
	def __init__(self, someFile):
		print "Construct SecureLogManager"
		self.theFile = someFile

	# The return value will be assigned to with as X
	def __enter__(self):
		print "__enter__"
		self.transLog = SecureLog(self.theFile)
		return self.transLog

	def __exit__(self, type, value, traceback):
		print "__exit__"
		if type is not None:
			pass # exception
		self.transLog.close()

logfile = open('log.log', 'w')
with SecureLogManager(logfile) as log:
	log.write('Some configuration')
	#raise Exception()

# use the contextlib provided decorator, so you don't have to write 
# a context class again
from contextlib import closing
with closing(SecureLog(open('log2.log', 'w'))) as log:
	log.write('Some other configuration')
	raise Exception()
