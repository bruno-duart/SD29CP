#include <iostream>
#define SIZE 800000000

int main(){
    double *arr = new double[SIZE];
    std::fill_n(arr, SIZE, 1234);

    for(long i=0; i < SIZE; i++)
        arr[i] = arr[i] / arr[i] + arr[i]/5 - 14;

    delete [] arr;
    return 0;
}