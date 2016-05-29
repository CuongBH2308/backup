"""
Euclid's Algorithm states that the greatest common divisor of two integers m
and n is n if n divides m evenly. However, if n does not divide m evenly, then
the answer is the greatest common divisor of n and the remainder of m divided
by n.
"""


def gcd(m, n):
    # it is ok if m > n, as the first round will switch the 2 numbers
    while m % n != 0:
        oldm = m
        oldn = n

        m = oldn
        n = oldm % oldn
    return n
