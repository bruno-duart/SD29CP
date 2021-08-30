#include <stdio.h>
#include <time.h>

#define NUM_FACT 1724
#define NUM_ITER 1000

long double factorial(int num){
    long double termo = 1;

    for(int i=num; i > 1; i--){
        termo *= (long double)i;
    }
    return termo;
}

int main(){
    long double last;
    clock_t time;
    printf("Calculando fatorial de 1 a %d, %d vezes\n", NUM_FACT, NUM_ITER);
    time = clock();
    for(int i = 0; i < NUM_ITER; i++){
        for(int j = 1; j <= NUM_FACT; j++){
            last = factorial(j);
        }
    }
    time = clock() - time;

    printf("Último fatorial calculado %Lf\n",last);
    printf("Tempo total %f\n", (double)time/CLOCKS_PER_SEC);

    return 0;
}