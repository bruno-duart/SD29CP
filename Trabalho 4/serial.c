#include <stdio.h>

#define NUM_FACT 1724
#define NUM_ITER 1000
#define RECURSIVE 0

long double factorial(int num){
    long double termo = 1;
    for(int i=num; i > 1; i--){
        termo *= (long double)i;
    }
    return termo;
}

long double recursive_factorial(int num){
    long double termo = 1;
    
    if(num == 1){
        return (long double)num;
    } else{
        return (long double)num*recursive_factorial(num-1);
    }
}

int main(){
    long double last;
    printf("Calculando fatorial de 1 a %d, %d vezes\n", NUM_FACT, NUM_ITER);
    #if RECURSIVE
        printf("Cálculo recursivo\n");
    #else
        printf("Cálculo iterativo\n");
    #endif
    for(int i = 0; i < NUM_ITER; i++){
        for(int j = 1; j <= NUM_FACT; j++){
            #if RECURSIVE
                last = recursive_factorial(j);
            #else
                last = factorial(j);
            #endif
            
        }
    }
    printf("Último fatorial calculado %Lf\n",last);

    return 0;
}