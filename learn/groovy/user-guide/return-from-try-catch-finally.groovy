def method(bool)
{
    try{
        if(bool) throw new Exception('foo')
        1
    }
    catch(e)
    {
        2
    }
    finally
    {
        // will be be part of the return value
        3
    }
}

assert method(false) == 1
assert method(true) == 2