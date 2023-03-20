#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>
#include <time.h>
#include <math.h>

void throws(long long n){
    //seed rand()
    time_t t;
    srand(&t);

    double x,y,distance_squared;
    long long in_circle=0;
    long long toss;
    for(toss=0; toss<n; toss++){
        x=pow(-1,(rand()/(RAND_MAX/2)))*(double)rand()/(double)RAND_MAX;
        y=pow(-1,(rand()/(RAND_MAX/2)))*(double)rand()/(double)RAND_MAX;
        distance_squared = (x*x)+(y*y);
        if(distance_squared<=1) in_circle++;
    }
    double pi_estimate = ((double)in_circle/(double)toss) * 4;
    printf("%f", pi_estimate);
}

int main(int argc, char *argv[]){
    int size, rank;
    //MPI_INIT(&argc, &argv);
    //MPI_Comm_size(&size, MPI_COMM_WORLD);

    //Get number of 
    
    long long num_throws=strtoll(argv[1], NULL, 10);
    
    throws(num_throws);

}


