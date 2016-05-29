@echo off

REM cmd.exe /c main_fast.cmd

echo current process id:
C:\Python34\python.exe %~dp0\show_parent_process_id.py

echo Main.cmd launch cmd by call
call %~dp0\show_parent_process_id.cmd

echo exit