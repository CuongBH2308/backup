import contextlib

# https://docs.python.org/release/2.5.2/lib/typecontextmanager.html
class ContextManagerDemo(object):
	def __enter__(self):
		print "__enter__ in with statement"
		return self

	def __exit__(self, exc_type, exc_val, exc_tb):
		print "__exit__ after with body"
		return False

	def dosth(self):
		print "dosth in with body"

with ContextManagerDemo() as demo:
	demo.dosth()

@contextlib.contextmanager
def tag(name):
	print "<%s>" % name
	yield
	print "</%s>" % name


with tag('html'):						# before yield
	print "This is a html document"		# After yield

@contextlib.contextmanager
def closing(obj):
	try:
		yield obj
	finally:
		thing.close()
		
class Thing:
	def close(self):
		print "Thing.close()"


thing = Thing()
with closing(thing) as obj:
	print "Before close Thing"

@contextlib.contextmanager
def assertRaises(exception_type):
	try:
		yield
	except exception_type as e:
		print "exception caught"

class Exception1(Exception): pass
class Exception2(Exception): pass
with assertRaises(Exception1):
	raise Exception1("")
with assertRaises(Exception1):
	raise Exception2("")


