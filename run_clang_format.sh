#!/bin/bash

# Source: https://stackoverflow.com/questions/28896909/how-to-call-clang-format-over-a-cpp-project-folder

THIS_PATH="$(realpath "$0")"
THIS_DIR="$(dirname "$THIS_PATH")"
SRC_DIR="$THIS_DIR/include"

FILE_LIST="$(find "$SRC_DIR" "$THIS_DIR/main.cpp" | grep -E ".*(\.ino|\.cpp|\.c|\.h|\.hpp|\.hh)$")"

echo -e "Files found to format = \n\"\"\"\n$FILE_LIST\n\"\"\""

clang-format --verbose -i --style=file $FILE_LIST