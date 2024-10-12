rmdir /S /Q .\build
mkdir .\build
cd .\build

@REM icpx -fsycl -Wall -shared ..\MH-SYCL.cpp -o MH-SYCL.dll

@REM # Compile the source files into object files
icpx -fsycl -Wall -c ..\test.cpp -o test.o
icpx -fsycl -Wall -c ..\MH-SYCL.cpp -o MH-SYCL.o

@REM # Link the object files into an executable with static Intel runtime
icpx -fsycl -static-intel test.o MH-SYCL.o -o test.exe

cd ..

