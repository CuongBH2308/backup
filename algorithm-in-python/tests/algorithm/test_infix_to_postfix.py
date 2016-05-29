import unittest
from algorithm.infix_to_postfix import infix_to_postfix
from algorithm.infix_to_postfix import infix_to_prefix
from algorithm.infix_to_postfix import eval_postfix
from algorithm.infix_to_postfix import eval_prefix

class TestInfixToPostfix(unittest.TestCase):
    def test_infix_to_postfix(self):
        self.assertEqual('AB-C+', infix_to_postfix('A-B+C'))
        self.assertEqual('ABC*-', infix_to_postfix('A-B*C'))
        self.assertEqual('AB-C*', infix_to_postfix('(A-B)*C'))
        self.assertEqual('ABC*+D+', infix_to_postfix('A+B*C+D'))
        self.assertEqual('AB+CD+*', infix_to_postfix('(A+B)*(C+D)'))
        self.assertEqual('AB*CD*+', infix_to_postfix('A*B+C*D'))
        self.assertEqual('AB+C+D+', infix_to_postfix('A+B+C+D'))

    def test_eval_postfix(self):
        self.assertEqual(2, eval_postfix('12-3+'))
        self.assertEqual(-5, eval_postfix('123*-'))
        self.assertEqual(-3, eval_postfix('12-3*'))
        self.assertEqual(11, eval_postfix('123*+4+'))
        self.assertEqual(21, eval_postfix('12+34+*'))
        self.assertEqual(14, eval_postfix('12*34*+'))
        self.assertEqual(10, eval_postfix('12+3+4+'))

    def test_infix_to_prefix(self):
        self.assertEqual('+-ABC', infix_to_prefix('A-B+C'))
        self.assertEqual('-A*BC', infix_to_prefix('A-B*C'))
        self.assertEqual('*-ABC', infix_to_prefix('(A-B)*C'))
        self.assertEqual('++A*BCD', infix_to_prefix('A+B*C+D'))
        self.assertEqual('*+AB+CD', infix_to_prefix('(A+B)*(C+D)'))
        self.assertEqual('+*AB*CD', infix_to_prefix('A*B+C*D'))
        self.assertEqual('+++ABCD', infix_to_prefix('A+B+C+D'))

    def test_eval_prefix(self):
        self.assertEqual(2, eval_prefix('+-123'))
        self.assertEqual(-5, eval_prefix('-1*23'))
        self.assertEqual(-3, eval_prefix('*-123'))
        self.assertEqual(11, eval_prefix('++1*234'))
        self.assertEqual(21, eval_prefix('*+12+34'))
        self.assertEqual(14, eval_prefix('+*12*34'))
        self.assertEqual(10, eval_prefix('+++1234'))
