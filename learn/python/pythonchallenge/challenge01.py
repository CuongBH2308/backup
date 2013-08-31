# http://www.pythonchallenge.com/pc/def/map.html


# A list of string method could be found here:
# 	http://docs.python.org/2/library/stdtypes.html#string-methods

import string
import unittest

def map_char(c):
	if not (c.isalpha() and c.islower()):
		return c
	a = ord('a')
	# map the character as c+2
	mc = (ord(c) - a + 2) % 26 + a
	return chr(mc)
	

data = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
print "".join([map_char(x) for x in data ])


intab = "".join([chr(x) for x in range(ord('a'), ord('z')+1)])
outtab = "".join([map_char(x) for x in intab])
transtab = string.maketrans(intab, outtab)

print data.translate(transtab)

url = "http://www.pythonchallenge.com/pc/def/map.html"
print url.translate(transtab)


# run unit test
class TestMapChar(unittest.TestCase):
	
	def setUp(self):
		print "setUp ..... "
	
	
	def test_simple(self):
		# usual case
		self.assertEqual(map_char('a'), 'c')
		self.assertEqual(map_char('c'), 'e')
		self.assertEqual(map_char('p'), 'r')
		
		# surpass case
		self.assertEqual(map_char('y'), 'a')
		self.assertEqual(map_char('z'), 'b')
		
		# not in scope
		self.assertEqual(map_char('@'), '@')
		self.assertEqual(map_char('*'), '*')
		self.assertEqual(map_char('9'), '9')
		self.assertEqual(map_char('/'), '/')
	
	def tearDown(self):
		print "tearDown .... "
		
unittest.main()