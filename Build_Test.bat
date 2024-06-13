rmdir /S /Q .\build
mkdir .\build
cd .\build

@REM icpx -fsycl -Wall test.cpp VectorConvolve-SYCL.cpp -o test.exe
icpx -fsycl -Wall -O2 ..\test.cpp -o test.exe

cd ..
