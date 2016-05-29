import unittest
from algorithm.balanced_brace import is_brace_balanced

class TestBalancedBrace(unittest.TestCase):
    def test_is_balanced(self):
        self.assertEqual(True, is_brace_balanced(''))
        self.assertEqual(True, is_brace_balanced('()'))
        self.assertEqual(True, is_brace_balanced('[]'))
        self.assertEqual(True, is_brace_balanced('{}'))
        self.assertEqual(True, is_brace_balanced('{[()]}'))
        self.assertEqual(True, is_brace_balanced('((((()))))'))
        self.assertEqual(True, is_brace_balanced('{[()][]({})}'))
        self.assertEqual(False, is_brace_balanced('[(])'))  # if use 3 stacks, you will missing such case
        self.assertEqual(False, is_brace_balanced('{')) 
        self.assertEqual(False, is_brace_balanced('[')) 
        self.assertEqual(False, is_brace_balanced('(')) 
        self.assertEqual(False, is_brace_balanced('}')) 
        self.assertEqual(False, is_brace_balanced(']')) 
        self.assertEqual(False, is_brace_balanced(')')) 

if __name__ == "__main__":
    unittest.main()