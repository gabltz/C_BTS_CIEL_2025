#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file.c>"
    exit 1
fi

file_c="$1"
exec="a.out"

cc "$file_c" 

if [ $? -eq 0 ]; then 
    echo "Build successful. $exec has been created"
else
    echo "Build failed. Check source"
fi

if [ -e "$exec" ]; then
    rm -f "$exec"
    echo "Old bin '$exec' deleted"
fi