class Stack(object):
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def top(self):
        return self.items[-1]

    def size(self):
        return len(self.items)

    def is_empty(self):
        return self.items == []

    def __str__(self):
        return self.items.__str__()


if __name__ == "__main__":
    def main():
        stack = Stack()
        stack.push('x')
        stack.push('y')
        stack.push('z')
        while not stack.is_empty():
            stack.pop()
            stack.pop()

    main()