IP=1.2.3.4
# 1. Use parameter expansion to replace . with ' '
#    pattern start with / (/.) means replace all
# 2. Space separated string could then be covert to an array use ()
# 	 like bash -c "arr=(1 2 3 4); echo ${arr[0]}"
IP_PARTS=(${IP//./ })
# Retrive an array element use: ${ARRAY[n]}
echo ${IP_PARTS[0]}
echo ${IP_PARTS[1]}