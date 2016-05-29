ns = {}
execfile('config.py', ns)

print "\n".join(sorted(dir(ns)))
print "*"*80
print ns['foo']
print ns['bar']
