@echo off

if "%*" == "" (
	set CL_DESC=default cl description
) else (
	set CL_DESC=%*	
)

p4 change -o | sed "s/<enter description here>/%CL_DESC%/" | p4 change -i