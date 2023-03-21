/*******************************
* @mainpage See files
* @file parallel_pi.c
* @author Victor LaBrie
* @date 20 March 2023
* @brief Monte Carlo algorithm for calculating pi 
*implemented in c using MPI.
*/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

/**
 * @brief The actual Monte Carlo alogithm
 * 
 * Generates points within a 2 by 2 grid from -1 to 1 on both
 * the x and y axes, and then determines how far it is from the 
 * origin. If the distance is less than or equal to 1, it is determined
 * to have fallen within the radius of the circle.
 * 
 * @param n : number of throws
 * @param rank : rank of process calling function, important for srand seed 
 * @return returns long long int representing number of hits
*/
long long throws(long long n, int rank){
    
    /**
     * @brief time and rank to seed the random number generator.
     * @code 
     * time_t t = time(NULL);
     * srand(t+rank);
     * @endcode
    */
    
    time_t t = time(NULL);
    srand(t+rank);
    //making sure seed is unique
    //printf("%ld ", rank+t);

    /**
     * @brief Monte Carlo algorithm
     * @code  double x,y,distance_squared;
     * long long in_circle=0;
     * long long toss;
     * for(toss=0; toss<n; toss++){
     *  x=pow(-1,(rand()/(RAND_MAX/2)))*(double)rand()/(double)RAND_MAX;
     *  y=pow(-1,(rand()/(RAND_MAX/2)))*(double)rand()/(double)RAND_MAX;
     *  distance_squared = (x*x)+(y*y);
     *  if(distance_squared<=1) in_circle++;
     * }
     * @endcode
    */
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


/**
 * @brief main function, handles mpi communication and management
 * @param argc
 * @param argv
 * @return 0 on success
*/
int main(int argc, char *argv[]){
    

    /**
     * @brief MPI initialization and setup
     * @code
     * int size, rank; 
     * MPI_Init(NULL,NULL);
     * MPI_Comm_size(MPI_COMM_WORLD, &size);
     * MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     * @endcode
    */
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

    /**
     * @brief Use of MPI_Reduce
     * @code MPI_Reduce(&local_hits, &total_hits, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
     * @endcode
     *  
    */

    MPI_Reduce(&local_hits, &total_hits, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(rank==0){
        //Was using to check if all local_hits were included in total_hits
        //printf("%llu ", total_hits);
        long double pi_estimate = ((long double)total_hits/(long double)num_throws)*4;
        printf("%.10Lf\n", pi_estimate);
    }
    MPI_Finalize();
    return 0;
}


