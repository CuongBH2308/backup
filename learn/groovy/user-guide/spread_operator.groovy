// Spread operator *.
assert ['cat', 'elephant']*.size() == [3, 8]
assert 'cat'.size() == 3

class Person { String name }
class Twin {
    Person one, two
    def iterator() {
        return [one, two].iterator()
    }
}

def tw = new Twin(one: new Person(name:'Tom'), two: new Person(name: 'Tim'))
assert tw*.name == ['Tom', 'Tim']
assert tw.collect { it.name } == ['Tom', 'Tim']

println (['hello', 'world']*.size())

