#include <iostream>
#define NUM_FACT 5

int main(){
    long num = 1;

    for(long i = NUM_FACT; i > 1; i--){
        num *= i;
    }

    std::cout << num << "\n";

    return 0;
}