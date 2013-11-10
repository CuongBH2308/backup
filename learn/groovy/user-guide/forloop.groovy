def y = 5
while(y-- > 0)
{
    println y
}
println''
y = 5
while(--y > 0)
{
    println y
}
println ''

// regular
for (int i = 0; i < 5; i++ )
{
    println i
}
println ''

// range
def sum = 0
for (i in 0..5){
    sum += i
}
println sum

// array
array = (0..4).toArray()
sum = 0
for ( i in array ) {
    sum += i
}
println sum
assert sum == 10

// list
for (i in [1,3,4,5])
{
    println i
}

// map
def map = ['abc':1, 'def':2, 'xyz':3]
for (e in map)
{
    println e.key
}

// string
for (c in 'text')
{
    println c
}
