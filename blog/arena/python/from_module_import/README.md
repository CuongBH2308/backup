### Problem:
You use =from base import *= to import variables to read module, and update the variable in write module, see if the update is seen by the read module - and the result is it can't

### Explaination:
* When you use =from base import *=, we create a new =pointers= to point to the memory of the variable.
* When you update the value in write.py: base.foo = 1000, what happened here is you actually let base.foo point to a differnt memory address, the original memory it point to doesn't change, that's why the value in read.py is not updated - it still point to the original memory address that is not changed.
* for base.demo, as I didn't change it memory address, I just update the value inplace for that object, so its change could be seen
# if you try base.demo = base.Demo('Updated Demo'), you will see it is not updated when read, as it points to a different object, while leave the orignal intact