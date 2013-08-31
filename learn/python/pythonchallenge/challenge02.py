# http://www.pythonchallenge.com/pc/def/ocr.html

import urllib2
import re
import operator
import collections
import logging

logging.basicConfig(level=logging.INFO) # DEBUG
logger = logging.getLogger(__name__)

logger.info("Request data from: http://www.pythonchallenge.com/pc/def/ocr.html")
f = urllib2.urlopen('http://www.pythonchallenge.com/pc/def/ocr.html')
assert(f)
logger.debug(f)

logger.info("Extract data from comment ...")
data = f.read()
comments = re.findall(r"<!--\s*(.*?)\s*-->", data, re.DOTALL) # allow . match newline
logger.debug("matched comments %s" % len(comments))
logger.debug("first comment: " + comments[0])
assert(len(comments) == 2)

logger.info("Analyze data ... ")
# use collections.OrderedDict to keep the insert order of the key
realdata = comments[1]
stats = collections.OrderedDict() 

for c in realdata:
	if not c in stats:
		stats[c] = 1
	stats[c] += 1
	
sorted_stats = sorted(stats.iteritems(), key=operator.itemgetter(1))
logger.debug(sorted_stats)

print "".join([ x for (x,y) in sorted_stats ])