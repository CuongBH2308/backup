#! /bin/sh

echo main.sh process id:
echo $$

echo normal call will start a new process
./show_process_id.sh


echo source call will execute in current process
. ./show_process_id.sh

echo exec call will replace current process
exec ./show_process_id.sh

echo Never here

