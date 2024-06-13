#include "Hamiltonian-SYCL.h"

#ifdef _WIN32
#define DllExport __declspec(dllexport)
#else
#define DllExport __attribute__((visibility("default")))
#endif

extern "C"{
    DllExport void Hamiltonian_SYCL_f(float res[], int N, const float vec[]){
        Hamiltonian_SYCL(res, N, vec);
    }
    DllExport void Hamiltonian_SYCL_d(double res[], int N, const double vec[]){
        Hamiltonian_SYCL(res, N, vec);
    }   
}