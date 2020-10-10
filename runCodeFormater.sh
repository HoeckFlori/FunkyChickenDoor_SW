#!/bin/bash

echo "Formating started..."
clang-format -i -style=file -fallback-style=LLVM src/*.cpp src/*.hpp
echo "...done"
