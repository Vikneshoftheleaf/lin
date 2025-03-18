#!/bin/bash

echo "Enter the filename:"
read Fname
echo " "

if [ -e "$Fname" ]; then
    echo "File exists"
    echo " "

    if [ -f "$Fname" ]; then
        echo "File is an ordinary file"
        echo " "
        echo "Content of the file is:"
        echo " "

        if [ -r "$Fname" ]; then
            cat "$Fname"
            echo " "
        fi

        if [ -w "$Fname" ]; then
            echo "You can update the file. Enter your text, and press Ctrl+D to save."
            cat >> "$Fname"
        fi

        echo " "
        echo "Updated file content is:"
        cat "$Fname"
    else
        echo "File is not an ordinary file"
    fi
else
    echo "File does not exist"
fi

