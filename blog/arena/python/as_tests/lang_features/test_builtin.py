import unittest
import math

class TestBuiltIn(unittest.TestCase):
	def test_reduce(self):
		self.assertEqual(5050, reduce(lambda x, y: x + y, range(1, 101)))

		self.assertEqual(math.factorial(10), reduce(lambda x, y: x * y, range(1, 11)))

		self.assertEqual('0123', reduce(lambda x,y: x+y, ['0', '1', '2', '3']))

		self.assertEqual(1234, reduce(lambda x, y: x*10+y, range(1,5)))


	def test_zip(self):
		''' take a tuple of list, return a list of tuples'''
		self.assertEqual([(1,4), (2,5), (3, 6)], zip([1,2,3], [4,5,6]))
		self.assertEqual([(1,4, 7), (2,5, 8), (3, 6, 9)], zip([1,2,3], [4,5,6], [7, 8, 9]))
