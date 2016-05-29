"""
I could design it with a TreeNode and a Tree class, but really, the Tree class will only contains a TreeNode as root,
and because you are using 2 different classes, it is not easy to write the algorithms in recursive way.

So, why not just one class, which represents both a TreeNode, and a Tree

"""
class Tree(object):
    def __init__(self, name, data = None):
        self.name = name
        self.data = data
        self.leftChild = None
        self.rightChild = None

    # Basic operations
    def insertLeft(self, name, data = None):
        self.leftChild = Tree(name, data)

    def insertRight(self, name, data = None):
        self.rightChild = Tree(name, data)

    def getLeftChild(self):
        return self.leftChild

    def getRightChild(self):
        return self.rightChild

    def getNodeName(self):
        return self.name

    # Traversal
    def preOrder(self):
        if self.leftChild:
            self.leftChild.preOrder()
        print(self.name, end = " ")
        if self.rightChild:
            self.rightChild.preOrder()

    def inOrder(self):
        print(self.name, end = " ")
        if self.leftChild:
            self.leftChild.inOrder()
        if self.rightChild:
            self.rightChild.inOrder()

    def postOrder(self):
        if self.leftChild:
            self.leftChild.postOrder()
        if self.rightChild:
            self.rightChild.postOrder()
        print(self.name, end = " ")

    # Algorithms - TODO
    def prettyPrint(self):
        pass

    def invert(self):
        tmp = self.leftChild
        self.leftChild = self.rightChild
        self.rightChild = tmp
        if self.rightChild:
            self.rightChild.invert()
        if self.leftChild:
            self.leftChild.invert()

if __name__ == '__main__':
    root = Tree('a')
    root.insertLeft('b')
    root.getLeftChild().insertRight('d')
    root.insertRight('c')
    root.getRightChild().insertLeft('e')
    root.getRightChild().insertRight('f')

    root.preOrder()
    print('')
    root.invert()
    root.preOrder()

