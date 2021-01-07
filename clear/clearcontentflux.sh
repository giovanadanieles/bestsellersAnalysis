#!/bin/bash

echo "Removing content not relevant (header and footer) from books taken from Project Gutenberg."
echo ""
echo $(date "+%Y-%m-%d_%H-%M-%S")
echo ""

mkdir /path

for livro in *.txt; do
      echo "# Livro: $livro"

      ./clearBook "$livro" "/path/"
done


echo ""
echo $(date "+%Y-%m-%d_%H-%M-%S")
