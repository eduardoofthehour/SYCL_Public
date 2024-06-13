cmake_minimum_required(VERSION 3.10)

# Define the project
project(HamiltonianSYCL)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Run the initialization script
if(WIN32)
    execute_process(COMMAND cmd /c "C:\\Program Files (x86)\\Intel\\oneAPI\\setvars.bat"
                    OUTPUT_VARIABLE init_output
                    ERROR_VARIABLE init_error
                    RESULT_VARIABLE init_result)
else()
    execute_process(COMMAND bash -c "source /path/to/your/init_script.sh"
                    OUTPUT_VARIABLE init_output
                    ERROR_VARIABLE init_error
                    RESULT_VARIABLE init_result)
endif()

if(NOT init_result EQUAL 0)
    message(FATAL_ERROR "Initialization script failed with error: ${init_error}")
endif()

# Specify the compiler and flags
set(CMAKE_CXX_COMPILER "C:\\Program Files (x86)\\Intel\\oneAPI\\compiler\\2024.1\\bin\\icpx.exe")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl -Wall -O2")

# Define the shared library target
add_library(HamiltonianSYCL SHARED ${CMAKE_SOURCE_DIR}/Hamiltonian-SYCL-Export.cpp)
set_target_properties(HamiltonianSYCL PROPERTIES OUTPUT_NAME "Hamiltonian-SYCL")

# Define the executable target
add_executable(test_exe ${CMAKE_SOURCE_DIR}/test.cpp)
set_target_properties(test_exe PROPERTIES OUTPUT_NAME "test")
