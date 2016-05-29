#!/bin/sh

echo main_fast.sh process id:
echo $$

echo run show_process_id.py:
./show_process_id.py

echo run show_process_id.py in background:
./show_process_id.py & # when run show_process_id in background to get its parent process id, but its parent process might already exit, then what you get is the system init process id
