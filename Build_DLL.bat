@REM https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html?operatingsystem=window&distributions=online          
rmdir /S /Q .\build
mkdir .\build
cd .\build

@REM see cmaketests.text in vector-add/src sample
@REM on windows -static-intel is ignored so there is no way to statically link  sycl libraries
icpx -fsycl -Wall -shared ..\Hamiltonian-SYCL-Export.cpp -o Hamiltonian-SYCL.dll

@REM see cmaketests.text in vector-add sample-FAILS
@REM icx-cl /EHsc -fsycl -Wall -shared ..\Hamiltonian-SYCL-Export.cpp -o Hamiltonian-SYCL.dll

cd ..

