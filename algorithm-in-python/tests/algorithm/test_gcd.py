import unittest
from algorithm.gcd import gcd

class TestGCD(unittest.TestCase):
    def test_gcd(self):
        self.assertEqual(2, gcd(2, 4))
        self.assertEqual(2, gcd(4, 2))

        self.assertEqual(6, gcd(18, 6))
        self.assertEqual(10, gcd(100, 90))


if __name__ == "__main__":
    unittest.main()