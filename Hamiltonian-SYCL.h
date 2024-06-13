// code is adapted from the file matrix_mul_sycl.cpp and vector-add-buffers.cpp
#pragma once

#include <vector>
#include <iostream>

#include <sycl/sycl.hpp>
// dpc_common.hpp can be found in the dev-utilities include folder.
// e.g., $ONEAPI_ROOT/dev-utilities/<version>/include/dpc_common.hpp
#include "dpc_common.hpp"
// #include "VectorConvolve-SYCL.h"

using namespace std;
using namespace sycl;

template <typename T>
void OffDiagonalHamiltonian(T res[], int N, const vector<T>& matrixVec, const T vec[]);

/*only floats work with my GPU, doubles throw exception*/
template <typename T>
void Hamiltonian_SYCL(T res[], int N, const T vec[]){
    vector<T> matrixVec(2*N-1), onedN(N), diagonal(N), sum1dN(N);

    matrixVec[N-1] = 0.;
    onedN[0] = sum1dN[0] = 0.;

    int j = N - 2, k = N;
    for(int i = 1; i < N ; i++, j--, k++){
        onedN[i] = 1./i;
        sum1dN[i] = sum1dN[i-1] + onedN[i];
        matrixVec[j] = matrixVec[k] = onedN[i];
    }

    for(int i = 0; i < N-1; i++){
        diagonal[i] = -(/* 1.5*onedN[i+1]+ */2.0*sum1dN[i]);
    }
    diagonal[N-1] = -(/* 1.5/N+ */2.0*sum1dN[N-1]);

    OffDiagonalHamiltonian(res, N, matrixVec, vec);

    for(int i = 0; i < N; i++){
        res[i] += vec[i]*diagonal[i];
    }

    return;
}

/* This is the expensive part we parallelize */
template <typename T>
void OffDiagonalHamiltonian(T res[], int N, const vector<T>& matrixVec, const T vec[]){
    // See VectorAdd
    // Create the range object for the vectors managed by the buffer.
    range<1> NRange{(size_t)N};

    // vector<T> resV(res, N), vecV(vec, N);

    // Create buffers that hold the data shared between the host and the devices.
    // The buffer destructor is responsible to copy the data back to host when it
    // goes out of scope.
    buffer vec_buf(vec, NRange);
    buffer M_buf(matrixVec);
    buffer res_buf(res, NRange);

    // Initialize the device queue with the default selector. The device queue is
    // used to enqueue kernels. It encapsulates all states needed for execution.
    try {
        queue q(default_selector_v);

        cout << "Device: " << q.get_device().get_info<info::device::name>() << "\n";
    
        // Submit command group to queue
        q.submit([&](auto &h) {
            accessor vec_acc(vec_buf, h, read_only);
            accessor M_acc(M_buf, h, read_only);
            accessor res_acc(res_buf, h, write_only);

            // Execute kernel.
            h.parallel_for(NRange/* range(N) */, [=](auto index) {
                T sum = 0.0f;
                auto offset = N - 1 - /*(int)*/index;
                for(int j = 0; j < N; j++){
                    sum+=M_acc[offset + j]*vec_acc[j];
                }

                res_acc[index] = sum;

            });
        });
        q.wait();
    } catch (sycl::exception const &e) {
        std::cout << "Caught SYCL exception: " << e.what() << "\n";
        // if (e.has_context()) {
        //     std::cout << "Context: " << e.get_context() << "\n";
        // }
        terminate();
    }

/*     a.clear();
    b.clear();
    sum_sequential.clear();
    sum_parallel.clear();
 */

    return;
}
