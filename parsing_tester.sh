#!/bin/bash
set -euo pipefail
shopt -s nullglob

# parameters
output_file="output.txt"
good_maps=(./maps/good/*)
bad_maps=(./maps/bad/*)

# Valgrind en tableau pour éviter les problèmes de quoting
valgrind_cmd=(
  valgrind
  --leak-check=full
  --track-origins=yes
  --show-leak-kinds=all
  --track-fds=yes
  --quiet
)

# compile the project
make -s re

# create/erase output file
: > "$output_file"

print_section() {
    printf "\n===========================================\n" >> "$output_file"
    printf "%s\n" "$1" >> "$output_file"
    printf "===========================================\n" >> "$output_file"
}

test_maps() {
    # itère sur tous les arguments reçus (chemins de maps)
    for map in "$@"; do
        echo "- Testing $map"
        printf ">>> %s\n" "$map" >> "$output_file"
        "${valgrind_cmd[@]}" ./cub3d "$map" >> "$output_file" 2>&1 || true
        printf "\n" >> "$output_file"
    done
}

print_section "GOOD MAPS"
test_maps "${good_maps[@]}"

print_section "BAD MAPS"
test_maps "${bad_maps[@]}"