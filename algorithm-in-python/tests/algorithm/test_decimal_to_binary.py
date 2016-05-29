import unittest
from algorithm.binary_decimal_conversion import decimal_to_binary_recursive, decimal_to_binary_stack
class TestDecimalToBinary(unittest.TestCase):
    def test_decimal_to_binary_recursive(self):
        self.assertEqual('0', decimal_to_binary_recursive(0))
        self.assertEqual('1', decimal_to_binary_recursive(1))
        self.assertEqual('101', decimal_to_binary_recursive(5))
        self.assertEqual('111', decimal_to_binary_recursive(7))
        self.assertEqual('100000', decimal_to_binary_recursive(32))

    def test_decimal_to_binary_stack(self):
        self.assertEqual('0', decimal_to_binary_stack(0))
        self.assertEqual('1', decimal_to_binary_stack(1))
        self.assertEqual('101', decimal_to_binary_stack(5))
        self.assertEqual('111', decimal_to_binary_stack(7))
        self.assertEqual('100000', decimal_to_binary_stack(32))
