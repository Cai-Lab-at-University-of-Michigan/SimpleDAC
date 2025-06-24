#!/bin/bash

cd /home/dev

mkdir build
cd build
cmake ..
make -j 12

exit