#!/bin/bash

i=1
for file in $(ls *.xpm | sort -V); do
    mv -- "$file" "${i}.xpm"
    ((i++))
done
