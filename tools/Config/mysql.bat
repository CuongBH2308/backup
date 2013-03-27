@echo off

rem start the server - mysqld.exe
rem If there are space in the path to executable, you need to pass in an 
rem additonal "title" as the first parameter
echo "Start mysqld.exe..."
start "" "D:\System\MySQL\MySQL Server 5.5\bin\mysqld.exe"


rem start mysql work bench
echo "Start MySQL Workbench..."
start "" "D:\System\MySQL\MySQL Workbench CE 5.2.36\MySQLWorkbench.exe"
