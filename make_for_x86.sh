#!/usr/bin/env bash
rm logging

# enable macro NDEBUG
echo "==== enable macro NDEBUG ===="
g++ example.cc -DNDEBUG -std=c++11 -o example && ./example
echo 

# disable macro NDEBUG
echo "==== disable macro NDEBUG ===="
g++ example.cc -std=c++11 -o example && ./example
