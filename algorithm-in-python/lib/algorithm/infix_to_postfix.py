# encoding:utf-8
#
# 理解：
# 转化的过程就是：
# 把高优先级的operator先放到output上去
# 因为优先级高的先算, 那是postfix evaluation的工作方式
# 所以：
# 1.遇到')'的时候，把stack上直到'('的内容放到output，因为()优先级最高
# 2.遇到一个operator的时候，把栈上比它优先级高的operator都放到output, 再把它放到栈上
#
from data_structure.stack import Stack
from collections import deque


def infix_to_postfix(expr):
    prec = {
        '(': 0,
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2
    }
    output = []
    s = Stack()
    # handle differently for 4 cases
    for c in expr:
        if c == '(':
            s.push(c)
        elif c == ')':
            while not s.is_empty() and s.top() != '(':
                output.append(s.pop())
            s.pop()
        elif c in prec:
            while not s.is_empty() and prec[s.top()] >= prec[c]:
                output.append(s.pop())
            s.push(c)
        else:
            output.append(c)

    while not s.is_empty():
        output.append(s.pop())

    return "".join(output)


oper = {
    '+': lambda a, b: a + b,
    '-': lambda a, b: a - b,
    '*': lambda a, b: a * b,
    '/': lambda a, b: a / b,
}


def eval_postfix(expr):
    s = Stack()
    for c in expr:
        if c in oper:
            b = int(s.pop())
            a = int(s.pop())
            s.push(oper[c](a, b))
        else:
            s.push(c)

    return s.pop()


def infix_to_prefix(expr):
    prec = {
        ')': 0,
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2
    }
    output = deque()
    s = Stack()
    # Process starting from the last item
    for c in expr[::-1]:
        if c == ')':
            s.push(c)
        elif c == '(':
            while not s.is_empty() and s.top() != ')':
                output.appendleft(s.pop())
            s.pop()
        elif c in prec:
            # notice it is not >= here, as we handling from right to left
            # so if it is equal, the one comes at left should handled first
            while not s.is_empty() and prec[s.top()] > prec[c]:
                output.appendleft(s.pop())
            s.push(c)
        else:
            output.appendleft(c)

    while not s.is_empty():
        output.appendleft(s.pop())

    return "".join(output)


def eval_prefix(expr):
    s = Stack()
    for c in expr[::-1]:  # from right to left
        if c in oper:
            a = int(s.pop())  # notice the order of a, b
            b = int(s.pop())
            s.push(oper[c](a, b))
        else:
            s.push(c)

    return s.pop()
