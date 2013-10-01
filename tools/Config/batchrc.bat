@echo off

REM ======================================================
REM ENVIRONMENT setup
REM ======================================================
set PROMPT=$P$_$$$S
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools\vsvars32.bat" 2>&1 > NUL

REM ======================================================
REM Driver subst
REM ======================================================

REM ======================================================
REM PATH Manipulation
REM ======================================================


REM ======================================================
REM doskey setup
REM ======================================================
doskey styletc=color 1F
doskey styledos=color 0F
doskey lddw=dumpbin /dependents $*

