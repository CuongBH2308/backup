1>2# : ^
'''
@echo off
setlocal
REM 05/07/2013
set d1=%DATE% 
REM 17:40:50.94
set t1=%TIME% 
call %*
set d2=%DATE%
set t2=%TIME%
echo ------------------------
echo Start:   %t1%
echo End:     %t2%
python "%~f0" 2>NUL
endlocal
exit /b
rem ^
'''

import os
from datetime import *

def create_datetime(date, time):
	dtdata = (os.environ[date].split()[0] + '/' + os.environ[time].replace(':','/').replace('.','/')).split('/');	
	if len(dtdata[0]) != 4:
		dtdata[0], dtdata[2] = dtdata[2], dtdata[0] # swap the day & year
	dtdata_int = [int(x) for x in dtdata]
	return datetime(*dtdata_int)

def days_hours_minutes_seconds_microseconds(td):
	days = td.days
	hours = td.seconds//3600
	minutes = (td.seconds//60)%60
	seconds = td.seconds % 60
	microseconds = td.microseconds
	return "{0} days {1} hours {2} minutes {3} seconds {4} microseconds".format(days, hours, minutes, seconds, microseconds)
	
dt1 = create_datetime('d1', 't1')
dt2 = create_datetime('d2', 't2')
elapsed = dt2 - dt1
print "Elapsed: " + days_hours_minutes_seconds_microseconds(elapsed)