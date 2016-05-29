
echo "=>The whole command line is: " "$@"

echo "=>The options are: "
for option in "$@" # options must come at the very first, then positional arguments
do
	if [[ $option == --* ]]
	then
		expr=${option:2} # ${parameter:offset:length} to get substring
		echo $expr
		eval $expr # --myoption won't work, we need an assignment
		shift # shift move away the leftmost parameter
	fi	
done

echo "=>The captured variables for options: "
set | tail -3 # set displays all environment variable and local variables (with locals at last)

echo "=>the positional arguments are: " "$@"
