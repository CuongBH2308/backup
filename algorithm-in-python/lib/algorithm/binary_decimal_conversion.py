from data_structure.stack import Stack

"""
Use simple examples to figure out the algorithm
1 = 1
2 = 10
3 = 11
4 = 100
5 = 101
7 = 111
mod = decimal % 2: the last bit
div = decimal / 2: to be recusively processed until 0 or 1
"""


def decimal_to_binary_recursive(decimal):
    if decimal in [0, 1]:
        return str(decimal)
    mod = decimal % 2
    div = decimal / 2
    return decimal_to_binary_recursive(div) + str(mod)


def decimal_to_binary_stack(decimal):
    s = Stack()
    while decimal > 1:
        mod = decimal % 2
        s.push(mod)
        div = decimal / 2
        decimal = div
    s.push(decimal)

    # convert stack to a string
    result = []
    while not s.is_empty():
        result.append(str(s.pop()))
    return "".join(result)
