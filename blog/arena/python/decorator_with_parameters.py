def welcome0(func):
    def new_func():
        print "welcome"
        func()
    return new_func

def welcome(name): # the decorator function takes the parameters
    def actual_decorator(func): # the actual decorator take the func as a parameter
            def new_func():
                print name + ' welcome you'
                func()
            return new_func
    return actual_decorator


@welcome0
@welcome('baiyan') # it is a function call, so it should return the actual decorator
def display():
    print "display"

display()
