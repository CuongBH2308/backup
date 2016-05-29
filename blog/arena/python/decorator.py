# decorator is a function which takes a function as parameter and return a function
# similar to AOP, to perform some kind of security/tracing/locking
# actually, the decorator doesn't have to be a function, it needs to be:
#   1. callable
#   2. the the result is a callable
# so a class as a decorator is also acceptable
#   1. constructor (takes a argument and returns a callable)
#   2. __call__
# there are a lot of decorators:
# 	https://wiki.python.org/moin/PythonDecoratorLibrary

# class-based decorator
class enter_exit:
	def __init__(self, f):
		print "Construct decorator"
		self.f = f

	def __call__(self):
		print '*' * 8 + "enter " + self.f.__name__ + '*' * 8
		self.f()
		print '*' * 8 + "exit " + self.f.__name__  + '*' * 8

# use @ to decorate
@enter_exit
def hello():
	print "Hello"
hello()

	
# directly call decorator
def hello2():
	print "Hello2"
hello2 = enter_exit(hello2)
hello2()


# function-based decorator
def authorize(f):
	def new_f():
		def is_authorized():
			# the authrization logic
			return True
		if is_authorized():
			print '*' * 8 + "Authorized user" + '*' * 8
			return f()
		else:
			print '*' * 8 + "Unauthorized user" + '*' * 8
			return False
	return new_f

@authorize
def hello3():
	print "Hello3"

hello3()