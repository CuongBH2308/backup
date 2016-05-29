#
#  * A metaclass is a class extends type and override __new__, so you can manipulate bases, attrs
# * metaclass is used to change the behavior when you define a new class, as long as that new class has a metaclass
#   defined
# * you can set metadata class either use class variable: __metaclass__, or derived from a base class which has metaclass
# * class decorator could be used to implement something that used to be implemented using meta class
# * python 3 use class LogDemo2(object, metaclass=LogMeta):, rather than __metaclass__ to set a metaclass
#
import types

class LogMeta(type):
    def __new__(meta, name, bases, attrs):
        print("call LogMeta::__new__")
        new_attrs = {}
        for attr, value in attrs.items():
            if isinstance(value, (types.FunctionType,)):
                def new_value(*args, **kwargs):
                    print("Start " + value.__name__)
                    value(*args, **kwargs)
                    print("End " + value.__name__)
                print("set " + attr + " to " + str(value))
                new_attrs[attr] = new_value # TODO: all functions are set to the same new_value, don't know why

        return type.__new__(meta, name, bases, new_attrs)


print ("Before defining LogBase")
class LogBase(object):
    __metaclass__ = LogMeta
print ("After defining LogBase")

print ("Before defining LogDemo1")
class LogDemo1(LogBase):
    def hello(self):
        print("hello")

    def world(self):
        print("world")
print ("After defining LogDemo1")

ld = LogDemo1()

print (ld.hello)
ld.hello()

print (ld.world)
ld.world()

print ("Before defining LogDemo2")
class LogDemo2(object):
    __metaclass__ = LogMeta
    def hello(self):
        print("hello")

    def world(self):
        print("world")
print ("After defining LogDemo2")

ld = LogDemo2()

print (ld.hello)
ld.hello()

print (ld.world)
ld.world()