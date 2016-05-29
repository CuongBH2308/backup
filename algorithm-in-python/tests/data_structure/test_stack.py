import unittest
from data_structure.stack import Stack

class TestStack(unittest.TestCase):
    def test_stack(self):
        s = Stack()
        self.assertEqual(True, s.is_empty())
        self.assertEqual(0, s.size())

        s.push(1)
        self.assertEqual(False, s.is_empty())
        self.assertEqual(1, s.size())

        s.push(True)
        s.push('Hello,World')
        self.assertEqual(3, s.size())

        self.assertEqual('Hello,World', s.pop())
        self.assertEqual(True, s.pop())

        s.pop()
        self.assertEqual(True, s.is_empty())

