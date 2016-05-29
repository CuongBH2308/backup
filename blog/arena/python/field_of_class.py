class Person:
	count = 0
	def __init__(self):
		print "New Person"
		Person.count = Person.count + 1 # you must reference it explictly through Person class


p1 = Person()
p1 = Person()

print Person.count