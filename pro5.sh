#!/bin/bash
if [ $# -ne 1 ]; then
echo "Usage: $0 <directory_path>"
exit 1
fi
directory=$1
if [ ! -d "$directory" ]; then
echo "Error: '$directory' is not a valid directory!"
exit 1
fi
echo "Scanning directory: $directory"
echo " "
ls -l "$directory" # List the directory contents in long format
echo " "
echo "Total items: $(ls -l "$directory" | wc -l)" # Count the number of items in the directory
