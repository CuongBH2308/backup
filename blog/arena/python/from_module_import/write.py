import base

def write():
	print "\nOriginal:"
	print "Original reference data id: " + str(id(base.demo))
	base.demo.name = "Updated Demo" # this will reflect that change
	#base.demo = base.Demo("Updated Demo") # this won't relfect the change
	print "Original data id: " + str(id(base.foo))
	base.foo = 1000	
	print "Original data id after assignment: " + str(id(base.foo))
