// https://stackoverflow.com/questions/36610775/how-does-one-setup-vc-dynamic-linking-via-command-line

#include <iostream>
#include <chrono>
#include <vector>

#include "Hamiltonian-SYCL.h"

using namespace std;
using namespace std::chrono;

#define PRINTARRAY(arr, len) \
    cout << "{"; \
    for(int i = 0; i < len-1 ; i++){ \
        cout << arr[i] << ", ";\
    } \
    cout << arr[len-1] << "}\n";

/* template <typename T>
void VectorConvolve(T res[], int N, const T vec[]);
 */
// template void VectorConvolve(float res[], int N, const float vec[]);
// void VectorConvolve(double res[], int N, const double vec[]);
// CExport DllExport void VectorConvolve(float res[], int N, const float vec[]);

int main(){
    constexpr int N = (int)1e6, N0 = 10;
    cout << "N: " << N << std::endl;
    
    /* 
    only works with floats otherwise gives:
        Device: Intel(R) Iris(R) Xe Graphics
        SYCL exception.
     */
    vector<float> vec(N, 0.), res(N);
    vec[N0-1] = 1.;

    cout << "First 10 elements of vec: ";
    PRINTARRAY(vec, 10);

    auto start = high_resolution_clock::now();
    Hamiltonian_SYCL<float>(res.data(), N, vec.data());
    auto stop = high_resolution_clock::now();

    cout << "First 10 elements of res: ";
    PRINTARRAY(res, 10);

    /* Calculate duration and cast to microseconds */
    auto duration = duration_cast<seconds>(stop - start);
    
    cout << "Time taken by function: " << duration.count() << "seconds" << std::endl;
   
    return 0;
}