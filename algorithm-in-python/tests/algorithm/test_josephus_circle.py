import unittest
from algorithm.josephus_circle import find_escape_position

class TestJosephusCircle(unittest.TestCase):
    def test_find_escape_position(self):
        self.assertEqual(1, find_escape_position(2, 2))
        self.assertEqual(3, find_escape_position(3, 2))
        self.assertEqual(1, find_escape_position(4, 3))
        self.assertEqual(5, find_escape_position(6, 7))
