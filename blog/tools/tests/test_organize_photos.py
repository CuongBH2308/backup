import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), os.pardir))
import unittest
from mock import MagicMock
import organize_photos as op

'''
Use nose, you could write test case in a very intuitive way - no skelenfolder needed, just write test_xxx functions would be enough

and yes, you can also use unittest.TestCase

Q:
    1. When the mock object will be invalidated?
    2. what assert function we can use?
'''
def test_get_target_dir():
    os.path.getmtime = MagicMock(return_value=1393759440.5243044)
    assert(op.get_target_dir('anyfile') == "2014-03")
    
    
class TestUseUnitTestFramework(unittest.TestCase):
    def test_move_to(self):
        def os_rename_mock(src, dst):
            assert(src == "D:\\Photo\\input\\2.jpg")
            assert(dst == "D:\\Photo\\2014-03\\2.jpg")
            
        os.rename = MagicMock(side_effect = os_rename_mock) # side effect means use another user defined function
        op.move_to("D:\\Photo\\input\\2.jpg", "D:\\Photo\\2014-03")
        def setUp(self):
            self.seq = list(range(10))
