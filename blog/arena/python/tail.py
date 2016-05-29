# Notices:
# 1. the 3rd parameter of open() is to disable file buffering
# 	 so file updated by another process could be picked up correctly
# 	 but since your focus is newly added tail, enable buffering is ok too
# 2. It is not necessary to fh.tell() to save the position, and then seek()
#	 to resume, as if readline() failed, the pointer stay still at the EOF

import sys
import time

filename = sys.argv[1]

with open(filename, 'r', 0) as fh:
	while True:
		line = fh.readline()
		if not line:
			time.sleep(1)
		else:
			print line