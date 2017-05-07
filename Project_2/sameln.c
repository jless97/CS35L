#!/bin/bash

# Set up the directory as the argument #
# create array to hold the regular files #

IFS=$'\n'
currentDirectory=$1
let currentFileNumber=0
declare -a filesInDirectory 


# Iterate through all files in directory, choosing only regular files #

currentFilesInDirectory=`ls -a $currentDirectory | sort`
for anotherFile in $currentFilesInDirectory
do
    if [[ ! -L "$currentDirectory/$anotherFile" && -r\
               "$currentDirectory/$anotherFile" ]]
    then
	if [ -f "$currentDirectory/$anotherFile" ]
	then
	    filesInDirectory[$currentFileNumber]="$currentDirectory/$anotherFile"
	    let currentFileNumber=currentFileNumber+1
	fi
    else
	echo "Either $anotherFile is a symbolic link or you don't have\
              read permissions for $anotherFile."
    fi
done	


# Base Case: If there are no duplicate files #

if [ $currentFileNumber -le 1 ]
then
    exit 0
fi


# Check for duplicate files #
# Then hardlink the duplicates based off lexicographically #

for (( i=0; i<$currentFileNumber; i++ ))
do
    for (( j=$i+1; j<$currentFileNumber; j++ ))
    do
	cmp -s -- "${filesInDirectory[$i]}" "${filesInDirectory[$j]}"
	if [ $? -eq 0 ]
	then
	    ln -f "${filesInDirectory[$i]}" "${filesInDirectory[$j]}"
	fi
    done
done
