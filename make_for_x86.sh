#!/usr/bin/env bash
rm logging

# enable macro NDEBUG
echo "==== enable macro NDEBUG ===="
g++ logging.cc -DNDEBUG -std=c++11 -o logging && ./logging
echo 

# disable macro NDEBUG
echo "==== disable macro NDEBUG ===="
g++ logging.cc -std=c++11 -o logging && ./logging 
