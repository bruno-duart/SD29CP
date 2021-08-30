#include <stdio.h>
#include <mpi.h>

#define NUM_FACT 1724
#define NUM_ITER 1000

long double factorial(int num, int start, int end, int rank){
    long double termo = 1;
    
    for(int i=end; i >= start; i--){
        termo *= (long double)i;
    }

    return termo;
}

int main(int argc, char **argv){
    long double last = 1, accum = 1;
    double time_init;
    int size, rank;
    int start, end;

    if (rank == 0) {
        printf("Calculando fatorial de 1 a %d, %d vezes\n", NUM_FACT, NUM_ITER);
    }

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0){
        time_init = MPI_Wtime();
    }

    for(int i = 0; i < NUM_ITER; i++){
        for(int j = 1; j <= NUM_FACT; j++){
            accum = 1;
            start = j * rank / size + 1;
            end = j * (rank + 1) / size;
            
            last = factorial(j, start, end, rank);

            if (rank != 0){
                MPI_Send(&last, 1, MPI_LONG_DOUBLE, 0, 1, MPI_COMM_WORLD);
            }
            else{
                for(long k = 1; k < size; k++){
                    MPI_Recv(&accum, 1, MPI_LONG_DOUBLE, k, 1, MPI_COMM_WORLD, &status);
                    last *= accum;
                }
           }
        }
    }
    if(rank == 0){
        double time_finish = MPI_Wtime();
        printf("Último fatorial calculado %Lf\n",last);
        printf("Tempo total %f\n", time_finish - time_init);
    }
    MPI_Finalize();

    return 0;
}