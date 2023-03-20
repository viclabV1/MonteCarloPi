#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

long long throws(long long n, int rank){
    //seed rand()
    time_t t;
    srand(t+rank);
    //making sure seed is unique
    //printf("%ld ", rank+t);
    double x,y,distance_squared;
    long long in_circle=0;
    long long toss;
    for(toss=0; toss<n; toss++){
        x=pow(-1,(rand()/(RAND_MAX/2)))*(double)rand()/(double)RAND_MAX;
        y=pow(-1,(rand()/(RAND_MAX/2)))*(double)rand()/(double)RAND_MAX;
        distance_squared = (x*x)+(y*y);
        if(distance_squared<=1) in_circle++;
    }
    return in_circle;
    //double pi_estimate = ((double)in_circle/(double)toss) * 4;
    //printf("%f", pi_estimate);
}

int main(int argc, char *argv[]){
    int size, rank;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    
    

    long long num_throws=strtoll(argv[1], NULL, 10);
    long long num_throws_per=num_throws/size;

    long long local_hits;
    long long total_hits;
    local_hits=throws(num_throws_per, rank);
    //printf("%llu ", local_hits);
    MPI_Reduce(&local_hits, &total_hits, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(rank==0){
        //Was using to check if all local_hits were included in total_hits
        //printf("%llu ", total_hits);
        long double pi_estimate = ((long double)total_hits/(long double)num_throws)*4;
        printf("%.7Lf\n", pi_estimate);
    }
    MPI_Finalize();
    return 0;
}


