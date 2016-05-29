#
# also known as disjoint set
# 1. Converge all users with the same email address as one user:
#   User1: email1, email2
#   User2: email2, email3
#   User3: email3, email4
#   Here User 1, 2, 3 are considerred as same user, even User1 and User2 has no
#   common emails
# 2. Converge all relatives
#   Person1 is relative with Person2
#   Person2 is relative with Person3
#  Here Person1, 2, 3 are relatives, although Person1 and Person3 not direct
#  relative
#
# This is a well known data structure called disjoint set:
#    http://en.wikipedia.org/wiki/Union_find
#


class DisjointSet(object):

    def __init__(self, size):
        self.fathers = range(size)  # element is represented by its index

    def union(self, index1, index2):
        root1 = self._get_root_father(index1)
        root2 = self._get_root_father(index2)

        if root2 != root1:
            self.fathers[root2] = root1

    def find(self, index):
        return self._get_root_father(index)

    def _get_root_father(self, index):
        if self.fathers[index] == index:
            return index
        return self._get_root_father(self.fathers[index])
