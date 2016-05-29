from algorithm.printer_simulation import simulation

print "5 pages per second"
for i in range(10):
    simulation(3600,5)

print ""
print "7 pages per second"
for i in range(10):
    simulation(3600,7)

print ""
print "10 pages per second"
for i in range(10):
    simulation(3600,10)