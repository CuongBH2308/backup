# Generator is a compact way to define an iterator with yield
# There are:
# 	1. generator functions (yield)
#   2. generator expression (as list comprehension)
# The advantage of generator is (compared to list)
# 	1. It is lazy generating, only generator when asked, so it is memory
# 	   efficient(if generated num takes memory), and with high performance 
#	   (if generating takes time)

# generator function
def fabonacci(limit=None):
	prev = 0
	cur = 0
	while True: # a loop is important to keep the iterating working
		if limit and cur > limit:
			break
		# yield the num to iterator
		yield cur 

		# when asked, compute the next number
		if cur == 0:
			cur = 1
		else:
			prev, cur = cur, prev + cur

print "unlimited fabonacci() generator < 100"
for i in fabonacci():
	if i > 100:
		break
	print i

# generator expression
print "unlimited even fabonacci() generator < 100"
even_fabonacci = (x for x in fabonacci() if x % 2 == 0)
for i in even_fabonacci:
	if i > 100:
		break
	print i

# list from generator (from iterator)
print "fabonacci list < 100"
fabonacci_list = [x for x in fabonacci(100)] # notice you can't use the unlimited generator here as the list will never complete
print "\n".join(str(x) for x in fabonacci_list)