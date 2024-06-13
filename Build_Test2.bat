rmdir /S /Q .\build
mkdir .\build
cd .\build

@REM see cmaketests.text in vector-add/src sample
@REM icpx -fsycl -Wall test.cpp VectorConvolve-SYCL.cpp -o test.exe

@REM see cmaketests.text in vector-add sample
@REM icx-cl IntelDPCPP -fsycl -Wall -O2 ..\test.cpp -o test.exe


icx-cl /EHsc -fsycl -Wall -O2 ..\test.cpp -o test.exe

cd ..
