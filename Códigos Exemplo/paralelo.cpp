#include <iostream>
#include <omp.h>
#define SIZE 800000000

int main(){
    omp_set_num_threads(2);
    double *arr = new double[SIZE];
    std::fill_n(arr, SIZE, 1234);

    #pragma omp_parallel for
    for(long i=0; i < SIZE; i++)
        arr[i] = arr[i] / arr[i] + arr[i]/5 - 14;

    delete [] arr;
    return 0;
}