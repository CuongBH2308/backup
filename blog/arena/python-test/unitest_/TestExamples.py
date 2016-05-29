import random
import unittest

def setUpModule():
    print "setUpModule"

def tearDownModule():
    print "tearDownModule"

# 1. each test is run with a new instance of the TestCase class (test fixture)
# 2. assertXXX method like assertEqual are used to accumulate results
class TestSequenceFunctions(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        print "setUpClass"

    @classmethod
    def tearDownClass(cls):
        print "tearDownClass"

    def setUp(self):
        print "\nsetUp"
        print id(self)
        self.seq = range(10)

    def tearDown(self):
        print "tearDown\n"

    def test_shuffle(self):
        print "test_shuffle"
        # make sure the shuffled sequence does not lose any elements
        random.shuffle(self.seq)
        self.seq.sort()
        self.assertEqual(self.seq, range(10))

        # should raise an exception for an immutable sequence
        self.assertRaises(TypeError, random.shuffle, (1,2,3))

    def test_choice(self):
        print "test_choice"
        # make sure the shuffled sequence does not lose any elements
        element = random.choice(self.seq)
        self.assertTrue(element in self.seq)

    @unittest.skip('skip a test')
    def test_sample(self):
        print "test_sample"
        with self.assertRaises(ValueError):
            random.sample(self.seq, 20)
        for element in random.sample(self.seq, 5):
            self.assertTrue(element in self.seq)

    @unittest.expectedFailure
    def test_demo_failure(self):
        self.assertTrue(False)

# 1. A TestCase with only 1 test looks like below
@unittest.skip('skip a TestCase')
class SimpleTest(unittest.TestCase):
    def runTest(self):
        self.assertTrue(1==1)

def before():
    pass
def legacyTest():
    print "Running a legacyTest"
    assert 1 == 1
def after():
    pass

legacyCase = unittest.FunctionTestCase(legacyTest, setUp = before, tearDown = after)


# 1. You can also run from: python -m unittest -v TestExamples.SimpleTest
# 2. Or use the discover command:
#    python -m unittest discover -p *.py
if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestSequenceFunctions)
    suite.addTest(unittest.TestLoader().loadTestsFromTestCase(SimpleTest))
    suite.addTest(legacyCase)

    unittest.TextTestRunner(verbosity=2).run(suite)
    #unittest.main()