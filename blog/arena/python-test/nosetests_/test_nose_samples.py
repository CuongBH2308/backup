import nose.tools
import time
# 1. files with executable bit set will be ignored
# 2. select test: nosetests test_nose_samples.py:test_1
# 3. select test: nosetests test_nose_samples:test_1
def test_1():
	assert (1 == 1)

def test_2():
	assert (1 == 1)

@nose.tools.timed(1)
def test_timeout():
	time.sleep(2)