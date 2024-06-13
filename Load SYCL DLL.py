import ctypes
import numpy as np
import os
import glob
dir = os.getcwd()
# Correctly format the search pattern to include spaces
search_pattern = os.path.join(dir, '**','Hamiltonian-SYCL.dll')

# Use glob to find all DLL files in the directory and subdirectories
dll_paths = glob.glob(search_pattern, recursive=True)

dll_names=[os.sep.join(f.split(os.sep)[-2:]) for f in dll_paths]
print('*********************')
print(dll_names)
print('\n')

# Example NumPy array
ln=5
vec = np.array([1.0, 2.0, 3.0, 4.0, 5.0], dtype=np.float32)
res = np.zeros((ln), dtype=np.float32)

# Convert NumPy array to C-compatible array
c_vec = (ctypes.c_float * ln)(*vec)
c_res = (ctypes.c_float * ln)(*res)

# Load the DLLs
print('*********************')
print(dll_names[1])
print('\n')

dll = dll_paths[1]
mylib = ctypes.CDLL(dll)
print(mylib)

# Define the function prototype by its name
mylib.Hamiltonian_SYCL_f.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.c_size_t, ctypes.POINTER(ctypes.c_float)]
mylib.Hamiltonian_SYCL_f.restype = None
mylib.Hamiltonian_SYCL_f(c_res, ln, c_vec)

print('*********************')
print(dll_names[0])
print('\n')

dll = dll_paths[0]
mylib = ctypes.CDLL(dll)
print(mylib)

# Define the function prototype by its name
mylib.Hamiltonian_SYCL_f.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.c_size_t, ctypes.POINTER(ctypes.c_float)]
mylib.Hamiltonian_SYCL_f.restype = None
mylib.Hamiltonian_SYCL_f(c_res, ln, c_vec)
