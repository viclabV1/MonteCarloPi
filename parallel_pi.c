/*******************************
* @mainpage See files
* @file parallel_pi.c
* @author Victor LaBrie
* @date 29 April 2023
* @brief Monte Carlo algorithm for calculating pi 
*implemented in c using PThreads.
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

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

//global variables
long long total_hits=0;
long randOffset=0;
pthread_mutex_t mutex;



void* throws(void* n_p);

/**
 * @brief main function
 * @param argc
 * @param argv
 * @return 0 on success
*/
    int main(int argc, char *argv[]){
    time_t start; 

    start = time(NULL);
    long thread_count=strtol(argv[1],NULL,10);
    long long num_throws=strtoll(argv[2], NULL, 10);
    long long num_throws_per=num_throws/thread_count;

    //printf("%llu ", local_hits);

    /**
     * @brief pthread stuff
     * @endcode
     *  
    */
    
    pthread_mutex_init(&mutex,NULL);
    pthread_t* thread_arr = (pthread_t*) malloc (thread_count*sizeof(pthread_t));


    for(long thread=0; thread<thread_count; thread++){
        pthread_create(&thread_arr[thread], NULL, throws, (void*)num_throws_per);
    }

    for(long thread=0; thread<thread_count; thread++){
        pthread_join(thread_arr[thread],NULL);
    }


    pthread_mutex_destroy(&mutex);
    long double pi_estimate = ((long double)total_hits/(long double)num_throws)*4;
    printf("%.15Lf\n", pi_estimate);
    printf("%f\n", (double)(time(NULL)-start));
    free(thread_arr);
    return 0;
    }

void* throws(void* n_p){
    /**
     * @brief time and rank to seed the random number generator.
     * @code 
     * time_t t = time(NULL);
     * srand(t+rank);
     * @endcode
    */
    
    long long n = (long long)n_p;
    
    //unique rand seeds for each thread
    time_t t = time(NULL);
    pthread_mutex_lock(&mutex);
    srand(t+randOffset);
    randOffset++;
    pthread_mutex_unlock(&mutex);
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
  
    pthread_mutex_lock(&mutex);
    total_hits += in_circle;
    pthread_mutex_unlock(&mutex);

    return NULL;
    //double pi_estimate = ((double)in_circle/(double)toss) * 4;
    //printf("%f", pi_estimate);
}
