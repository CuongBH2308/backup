@echo off

echo 1. main.cmd launch python directly:
C:\Python34\python.exe %~dp0\show_parent_process_id.py

echo 2 main.cmd launch cmd by call
call %~dp0\show_parent_process_id.cmd

echo 3 main.cmd launch cmd by start - which runs in a new process:
start /b %~dp0\show_parent_process_id.cmd

echo 4 main.cmd launch cmd by default:
%~dp0\show_parent_process_id.cmd

echo Never here
