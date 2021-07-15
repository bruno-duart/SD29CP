#include <iostream>
#define NUM_FACT 70

int main(){
    unsigned long long int num = 1;

    for(unsigned long long int i = NUM_FACT; i > 1; i--){
        num *= i;
    }

    std::cout << num << "\n";

    return 0;
}