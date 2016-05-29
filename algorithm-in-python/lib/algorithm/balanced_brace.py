from data_structure.stack import Stack


def is_pair(lhs, rhs):
    opens = '{[('
    closers = '}])'
    return opens.index(lhs) == closers.index(rhs)


def is_brace_balanced(expr):
    assert isinstance(expr, str), 'argument must be of str type'
    stack = Stack()
    for char in expr:
        if char in "{[(":
            stack.push(char)
        elif char in "}])":
            if (not stack.is_empty()) and is_pair(stack.top(), char):
                stack.pop()
            else:
                return False

    return stack.is_empty()
