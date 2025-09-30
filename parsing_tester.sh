#!/bin/bash

# parameters
output_file="output.txt"
good_maps=(./maps/good/*)
bad_maps=(./maps/bad/*)
valgrind_args="valgrind --leak-check=full --track-origins=yes \
--show-leak-kinds=all --track-fds=yes --quiet"

# compile the project
make re

echo "- Running tests ..."
# create/erase output file
: > "$output_file"

# test every map and retrieve output
echo "***************************************" >> "$output_file"
echo "              Good maps" >> "$output_file"
echo "***************************************" >> "$output_file"
for map in "${good_maps[@]}"; do
    echo ">>> Testing $map"
    echo ">>> Testing $map" >> "$output_file"
    $valgrind_args ./cub3d "$map" >> "$output_file" 2>&1
    echo "" >> "$output_file"
	echo "---------------------------------------" >> "$output_file"
    echo "" >> "$output_file"
done

echo "***************************************" >> "$output_file"
echo "               Bad maps" >> "$output_file"
echo "***************************************" >> "$output_file"
for map in "${bad_maps[@]}"; do
    echo ">>> Testing $map"
    echo ">>> Testing $map" >> "$output_file"
    $valgrind_args ./cub3d "$map" >> "$output_file" 2>&1
    echo "" >> "$output_file"
	echo "---------------------------------------" >> "$output_file"
    echo "" >> "$output_file"
done
