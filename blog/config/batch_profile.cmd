@echo off

REM TODO: bash



REM alias
doskey sublime="C:\Program Files\Sublime Text 2\sublime_text.exe" $*
doskey python3=C:\Python34\python.exe $*


REM JAVA
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_31

REM PATH
set PATH=C:\Program Files\Java\jdk1.8.0_31\bin;%PATH%
set PATH=C:\Tools\gradle-2.6\bin;%PATH%
set PATH=C:\Tools\apache-maven-3.3.3\bin;%PATH%

REM windows system tools
set PATH=C:\Program Files\SysinternalsSuite;%PATH%

REM My Tools
set PATH=C:\Workspace\github\blog\tools;%PATH%

cd C:\Workspace