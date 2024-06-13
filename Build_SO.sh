#!/bin/bash

# https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html?operatingsystem=window&distributions=online          
rm -rf ./build
mkdir ./build
cd ./build

# on linux -static-intel can be used to statically link sycl libraries
icpx -fsycl -Wall -shared -fPIC -static-intel ../Hamiltonian-SYCL-Export.cpp -o Hamiltonian-SYCL.so

cd ..