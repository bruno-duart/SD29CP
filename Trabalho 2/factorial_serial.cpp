/*
    #####################################################
    ####        Sistemas Distribuídos - SD29CP       ####
    ####        Trabalho 2 - Threads, OpenMP         ####
    ####      Cálculo de fatorial - versão serial    ####
    ####                Bruno Duarte                 ####
    ####       brunoduarte@alunos.utfpr.edu.br       ####
    #####################################################
*/

#include <iostream>
#define NUM_FACT 1754

long double factorial(int* num){
    long double termo = 1;
    for(int i=*num; i > 1; i--){
        termo *= (long double)i;
    }
    return termo;
}

int main(){

    for(int i = 0; i < 10000; i++){
        for(int i = 1; i <= NUM_FACT; i++){
            //std::cout << "Fatorial de " << i << " = " << factorial(&i) << "\n";
            factorial(&i);
        }
    }
    //std::cout << num << "\n";

    return 0;
}