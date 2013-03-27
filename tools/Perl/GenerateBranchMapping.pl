#####
# 
# Description: This script will generate a file mapping between 2 branches in case there are any file moves, for example, MP to LB, and LB to Main
# 
# Algorithm:
# 1. List all files from 2 branches and store them in 2 maps
# 2. For each file from map1, check if the file exist in map2
#    yes:
#        this is a non-moved file, remvoe it from both maps
#    no:
#        1) This file is newly added in branch1 
#		    Remove it from map1
#        2) This file is moved from another place in branch1
#			Locate the source, check if the source exist on branch2:
#			yes: 
#				add <target-source> to branch mapping
#			no: 
#				this file is also moved in branch2, locate the target2, add <target-target2> tp branch mapping (remove)
#        3) This file has been moved in branch2
#			Locate the target in branch2, add <source-target2> to branch mapping (remove)
# 3. For each file in map2, check if the file exist in map1
# 	 same as step2
#
# Usage:
# GenerateBranchMapping.pl <Branch1> <Branch2> <StartTime> [EndTime]
# 
# Author: Baiyan Huang
# Date: 9/7/2010
#
#####