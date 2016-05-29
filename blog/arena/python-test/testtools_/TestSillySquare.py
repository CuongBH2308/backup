from testtools import TestCase
from testtools import ExpectedException
from testtools.matchers import Equals
from testtools.content import text_content, attach_file, Content
from testtools.content_type import UTF8_TEXT
import silly


class IsDivisibleByMismatch(object):
    def __init__(self, number, divider, remainder):
        self.number = number
        self.divider = divider
        self.remainder = remainder

    def describe(self):
        return "%r is not divisible by %r, %r remains" % (
            self.number, self.divider, self.remainder)

    def get_details(self):
        return {}

class IsDivisibleBy(object):
    """Match if a number is divisible by another number."""
    def __init__(self, divider):
        self.divider = divider
    def __str__(self):
        return 'IsDivisibleBy(%s)' % (self.divider,)
    def match(self, actual):
        remainder = actual % self.divider
        if remainder != 0:
        	# or 
        	# return Mismatch(
            # "%r is not divisible by %r, %r remains" % (
            #    actual, self.divider, remainder))
            return IsDivisibleByMismatch(actual, self.divider, remainder)
        else:
            return None



# 1. python -m testtools.run TestSillySquare
# 2. python -m testtools.run discover
class TestSillySquare(TestCase):
	def test_square(self):
		def cleanup():
			print "addCleanup"
		self.addCleanup(cleanup)
		result = silly.square(7)
		self.assertEqual(result, 49) # it is implmented using assertThat anyway

	def test_square_2(self):
		self.addDetail('arbitrary-color-name', text_content('blue'))
		self.addDetail('log-file', Content(UTF8_TEXT, lambda: open('log.txt', 'r').readlines()))
		result = silly.square(7)
		self.assertThat(result, Equals(49))

	def test_square_bad_input(self):
		self.assertRaises(TypeError, silly.square, "organge")

	def test_square_bad_input_2(self):
		with ExpectedException(TypeError, "can't multiply.*"):
			silly.square('organge')

	def test_expect_failure_example(self):
	    self.expectFailure(
	        "cats should be dogs", self.assertEqual, 'cats', 'dogs')

	def test_is_divisible_by_example(self):
	    # This succeeds, since IsDivisibleBy(5).match(10) returns None.
	    self.assertThat(10, IsDivisibleBy(5))
	    # This fails, since IsDivisibleBy(7).match(10) returns a mismatch.
	    self.assertThat(10, IsDivisibleBy(2))