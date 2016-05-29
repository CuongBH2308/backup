count = 0

fh = [] 
# if you don't store the filehandler
# it would be GCed when not referenced
# hence the file will be closed
while True:
	filename = 'file_%s' % count
	count = count + 1
	f = open(filename, 'w')
	print count
	fh.append(f)
