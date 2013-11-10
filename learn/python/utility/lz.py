import re
import os
import unittest

def _discover(module, filter):
	members = dir(module)
	filter_members = [x for x in members if re.search(filter, x)]
	return filter_members

def dis(module, filter=r''):
	print os.linesep.join(_discover(module, filter))
	
if __name__ == "__main__":
	import string
	dis(string, r'^c.*')
	