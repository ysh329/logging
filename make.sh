#!/usr/bin/env bash
rm logging
g++ logging.cc -std=c++11 -o logging && ./logging
