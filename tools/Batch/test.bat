1># : ^
'''
set t1 = %TIME%
call %*
set t2 = %TIME%
python %~f0"
exit /b
rem ^
'''