assert (1 << 2) == 4
assert (4 >> 1) == 2
assert (15 >>> 1) == 7
assert (3 | 6) == 7
assert (3 & 6) == 2
assert (3 ^ 6) == 5 //xor

int mostlyOnes = 0xFFFFFFFE
assert ~mostlyOnes == 1