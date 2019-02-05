#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "q1.h"

pthread_mutex_t chops [1000];

int phioFed, numPhilo, numNom;


void  runq1(int argc, char *argv[]){
    phioFed  = 0;
    numPhilo = 0;
    numNom = 0;
    pthread_t thread[1000];
    

    //int thread_id[1000];
    int *thread_id  = NULL;
    thread_id = calloc(1000, sizeof(int));

    //int id = 0;
    int result = 0;
    //int isLocked = 0;

    //Get number of philo and number of times to eat
    if(argv[1] == NULL){
        printf("Invalid command line argument\n");
        printf("Run again!!\n");
        exit(0);
    }
    if(argv[2] == NULL){
        printf("Invalid command line argument\n");
        printf("Run again!\n");
        exit(0);
    }
    
  
   if(argv[1] != NULL){
       numPhilo = atoi(argv[1]);
   }
   
   if(argv[2] != NULL){

       numNom = atoi(argv[2]);
   }

    //Create mutex/execute function
    for (int i = 0; i < numPhilo; i = i +  1) {
        //thread_id[i] = i;
        thread_id[i] = 0;
        if(i >= 0){
            thread_id[i] = i;
        }
        if(i >= 0){
            result = pthread_create(&(thread[i]), NULL, &philoDiner, &(thread_id[i]));
            pthread_mutex_init(&chops[i], NULL);
        }
    }

    if(result < 1){
        
    }


    //Join the threads
    for (int c = 0; c < numPhilo; c = c + 1) {
        if(c >= 0){
            result = pthread_join(thread[c], NULL);
        }
    }
    //Kill the threads
    for (int c = 0; c < numPhilo; c = c + 1) {
        if(c >= 0){
            result = pthread_mutex_destroy(&chops[c]);
        }
    }


    //return 0;
}


void *philoDiner(void *arg) {
    int minId;
    minId = 0;
    int fatty;
    fatty =  0;

    int id;
    id = *((int*) arg);
    minId = id - 1;
    //Wrap around for begining and end
    if (minId == -1){
       // minId = numPhilo - 1;
       minId = numPhilo;
       minId--;
    }

    //For as many times as they have to eat
    while (fatty < numNom) {
        //Lock 1 and 2
        printf("Philosopher %d Waiting...\n", id + 1);
        pthread_mutex_lock(&chops[id]);
        pthread_mutex_lock(&chops[minId]);
        fatty++;
        sleep(1);

       // printf("Philosopher %d Eating....\n", id + 1);
        printPhiloEating(id + 1);
        pthread_mutex_unlock(&chops[id]);
        pthread_mutex_unlock(&chops[minId]);
        //printf("Philosopher %d has eaten!\n", id + 1);
        printPhiloHasEaten(id + 1);

    }
    phioFed++;
    return NULL;

}

void printPhiloEating(int id){

    printf("Philosopher %d Eating....\n", id);
}

void printPhiloHasEaten(int id){

     printf("Philosopher %d has eaten!\n", id);
}