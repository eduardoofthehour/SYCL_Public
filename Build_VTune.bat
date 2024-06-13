rmdir /S /Q .\build
mkdir .\build
cd .\build

@REM icpx -fsycl -Wall test.cpp VectorConvolve-SYCL.cpp -o test.exe
icpx -fsycl -Wall -gline-tables-only -fdebug-info-for-profiling -O2 -g ..\test.cpp ..\VectorConvolve-SYCL.cpp -o test.exe

cd ..
