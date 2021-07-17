/*
    #####################################################
    ####        Sistemas Distribuídos - SD29CP       ####
    ####        Trabalho 2 - Threads, OpenMP         ####
    ####    Cálculo de fatorial - versão paralelo    ####
    ####                Bruno Duarte                 ####
    ####       brunoduarte@alunos.utfpr.edu.br       ####
    #####################################################
*/

#include <iostream>
#include <omp.h>
#define NUM_FACT 1754

long double factorial(int* num){ // Cálculo de fatorial
    long double termo = 1;
    for(int i=*num; i > 1; i--){
        termo *= (long double)i;
    }
    return termo;
}

int main(){
    omp_set_num_threads(16);
    for(int i = 0; i < 10000; i++){
        #pragma omp parallel for
        for(int i = 1; i <= NUM_FACT; i++){
            //std::cout << "Fatorial de " << i << " = " << factorial(&i) << "\n";
            factorial(&i);
        }
    }

    return 0;
}