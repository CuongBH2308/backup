import unittest

class TestProperty(unittest.TestCase):
    def test_create_class(self):
        def add(self, a, b):
            return a + b

        DemoClass = type('DemoClass', (object,), {'age': 1, 'add': add})
        d = DemoClass()
        self.assertEqual(3, d.add(1, 2))
        self.assertEqual(1, d.age)

    def test_isinstance(self):
        '''isinstance is a preferred way to test object types, rather than type()'''

        class TestClass(object): pass

        self.assertTrue(isinstance(1, int))
        self.assertTrue(isinstance('', str))

        t = TestClass()
        self.assertTrue(t, TestClass)
        self.assertTrue(isinstance(TestClass, type))

