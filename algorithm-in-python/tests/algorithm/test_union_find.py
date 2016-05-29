import unittest
from algorithm.union_find import DisjointSet

class TestUnionFind(unittest.TestCase):
    def test_union_find(self):
        s = DisjointSet(6)
        s.union(1, 2)
        s.union(2, 3)

        s.union(4, 5)
        s.union(4, 0)

        self.assertEqual(s.find(1), s.find(2))
        self.assertEqual(s.find(2), s.find(3))

        self.assertEqual(s.find(0), s.find(4))
        self.assertEqual(s.find(4), s.find(5))
        
        self.assertNotEqual(s.find(4), s.find(1))

    def test_union_find_size_1(self):
        s = DisjointSet(1)

        s.union(0, 0)

        self.assertEqual(0, s.find(0))
