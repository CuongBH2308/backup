import unittest

class TestExtract3rdElement(unittest.TestCase):
    def setUp(self):
        self.data = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        self.expected = [0, 3, 6, 9]

    # slice: 1
    def test_use_list_slice(self):
        self.assertEqual(self.expected, self.data[0::3]) # data[start::step]

    # map/filter/listcomprehension: 4
    def test_use_enumerate_with_map_filter(self):
        self.assertEqual(self.expected, map(lambda x: x[1], filter(lambda x: x[0] % 3 == 0, enumerate(self.data))))

    def test_use_enumerate_with_list_comprehension(self):
        self.assertEqual(self.expected, [x for i, x in enumerate(self.data) if i % 3 == 0 ])

    def test_use_enumerate_with_filter_and_list_comprehension(self):
        self.assertEqual(self.expected, [x[1] for x in filter(lambda e: e[0] % 3 == 0, enumerate(self.data))])

    def test_use_enumerate_with_map_and_list_comprehension(self):
        self.assertEqual(self.expected, map(lambda x: x[1], [x for x in enumerate(self.data) if x[0] % 3 == 0]))

    # loop: 3
    def test_use_enumerate_with_loop(self):
        output = []
        for i, x in enumerate(self.data):
            if i % 3 == 0:
                output.append(x)
        self.assertEqual(self.expected, output)

    def test_use_loop(self):
        i = 0
        output = []
        for x in self.data:
            if i % 3 == 0:
                output.append(x)
            i += 1
        self.assertEqual(self.expected, output)

    def test_use_index_plus3_loop(self):
        i = 0
        output = []
        while i < len(self.data):
            output.append(self.data[i])
            i += 3

    # yield: n
    def test_use_yield(self): # and the solutions above could be replace with yield as generators
        pass