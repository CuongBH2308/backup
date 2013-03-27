@echo off

for /f "tokens=*" %%i in ('dir /b') do du -s -h "%%i"
rem du -s -h
