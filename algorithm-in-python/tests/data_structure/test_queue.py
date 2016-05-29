import unittest
from data_structure.queue import Queue

class TestQueue(unittest.TestCase):
    def test_queue(self):
        q = Queue()
        self.assertEqual(True, q.is_empty())
        self.assertEqual(0, q.size())

        q.enqueue(1)
        self.assertEqual(False, q.is_empty())
        self.assertEqual(1, q.size())

        q.enqueue(True)
        q.enqueue("Hello, World")
        self.assertEqual(3, q.size())

        self.assertEqual(1, q.dequeue())
        self.assertEqual(True, q.dequeue())
        self.assertEqual(1, q.size())

        q.dequeue()
        self.assertEqual(True, q.is_empty())


