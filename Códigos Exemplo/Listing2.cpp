#include <iostream>

int main(){
    #pragma omp parallel num_threads(2)
    {
        std::cout << "Hello World\n";
    }
}