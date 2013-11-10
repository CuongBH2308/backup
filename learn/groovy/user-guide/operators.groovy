def func1()
{
    def a = null
    def b = "foo"
    
    assert a != b
    assert b != a
    assert a == null
}
func1()

def func2()
{
    Byte a = 12
    Double b = 10
    assert a instanceof Byte
    assert b instanceof Double
    
    assert a > b
    
    Short c = 13
    Integer d = 14
    
    Float e = 17
}
func2()