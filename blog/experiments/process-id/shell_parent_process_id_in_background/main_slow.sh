#!/bin/sh

echo main_fast.sh process id:
echo $$

echo run show_process_id.py:
./show_process_id.py

echo run show_process_id.py in background:
./show_process_id.py &

sleep 2
