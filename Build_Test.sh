#!/bin/bash

# https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html?operatingsystem=window&distributions=online          
rm -rf ./build
mkdir ./build
cd ./build

# on linux -static-intel can be used to statically link sycl libraries
icpx -fsycl -Wall -static-intel ../test.cpp -o test.exe

cd ..