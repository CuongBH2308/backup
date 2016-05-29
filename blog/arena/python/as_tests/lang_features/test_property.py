import unittest

class Demo(object):
    def __init__(self):
        self._foo = 0

    @property
    def foo(self):
        return self._foo

    @foo.setter
    def foo(self, value):
        self._foo = value

    @foo.deleter
    def foo(self):
        del self._foo


class TestProperty(unittest.TestCase):
    def test_property(self):

        d = Demo()
        self.assertEqual(0, d.foo)

        d.foo = 100
        self.assertEqual(100, d.foo)

        del d.foo
        with self.assertRaises(AttributeError):
            d.foo
