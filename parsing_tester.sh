#!/bin/bash

# parameters
output_file="output.txt"
good_maps=(./maps/good/*)
bad_maps=(./maps/bad/*)
valgrind_args="valgrind --leak-check=full --track-origins=yes \
--show-leak-kinds=all --track-fds=yes --quiet"

# compile the project
make re

# create/erase output file
: > "$output_file"

# test every map and retrieve output
echo "================ GOOD MAPS ================" >> "$output_file"
for map in "${good_maps[@]}"; do
    echo "- Testing $map"
    echo ">>> $map" >> "$output_file"
    $valgrind_args ./cub3d "$map" >> "$output_file" 2>&1
    echo "" >> "$output_file"
done
echo "================ BAD MAPS =================" >> "$output_file"
for map in "${bad_maps[@]}"; do
    echo "- Testing $map"
    echo ">>> $map" >> "$output_file"
    $valgrind_args ./cub3d "$map" >> "$output_file" 2>&1
    echo "" >> "$output_file"
done
