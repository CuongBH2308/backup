import unittest
from mock import * # Mock, MagicMock, patch, create_autospec
from prettytable import PrettyTable

class TestPrettyTable(unittest.TestCase):
    def test_prettytable(self):
    	print ""
        x = PrettyTable(['Name', 'Title', 'Age'])
        x.align['Name'] = '1'
        x.add_row(['baiyanh', 'VP', 34])
        x.add_row(['vetterbr', 'ED', 44])
        x.add_row(['pfox', 'ED', 54])
        print x


