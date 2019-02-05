#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "q1.h"
#include "q2.h"

//  pthread_mutex_t chops [1000];
// // // int phioFed = 0;
// // // int numPhilo = 0;
// // // int numNom = 0;
//  int phioFed, numPhilo, numNom;
// // //phioFed = numPhilo = numNom = 0;

// int main(int argc, char *argv[]) {
//     phioFed  = 0;
//     numPhilo = 0;
//     numNom = 0;
//     pthread_t thread[1000];

//     //int thread_id[1000];
//     int *thread_id  = NULL;
//     thread_id = calloc(1000, sizeof(int));

//     //int id = 0;
//     int result = 0;
//     //int isLocked = 0;

//     //Get number of philo and number of times to eat
//     if(argv[1] == NULL){
//         printf("Invalid command line argument\n");
//         printf("Run again!!\n");
//         exit(0);
//     }
//     if(argv[2] == NULL){
//         printf("Invalid command line argument\n");
//         printf("Run again!\n");
//         exit(0);
//     }
    
  
//    if(argv[1] != NULL){
//        numPhilo = atoi(argv[1]);
//    }
   
//    if(argv[2] != NULL){

//        numNom = atoi(argv[2]);
//    }

//     //Create mutex/execute function
//     for (int i = 0; i < numPhilo; i = i +  1) {
//         //thread_id[i] = i;
//         thread_id[i] = 0;
//         if(i >= 0){
//             thread_id[i] = i;
//         }
//         if(i >= 0){
//             result = pthread_create(&(thread[i]), NULL, &philoDiner, &(thread_id[i]));
//             pthread_mutex_init(&chops[i], NULL);
//         }
//     }

//     if(result < 1){
        
//     }


//     //Join the threads
//     for (int c = 0; c < numPhilo; c = c + 1) {
//         if(c >= 0){
//             result = pthread_join(thread[c], NULL);
//         }
//     }
//     //Kill the threads
//     for (int c = 0; c < numPhilo; c = c + 1) {
//         if(c >= 0){
//             result = pthread_mutex_destroy(&chops[c]);
//         }
//     }


//     return 0;
// }

// // void *philoDiner(void *arg) {
// //     int minId;
// //     minId = 0;
// //     int fatty;
// //     fatty =  0;

// //     int id;
// //     id = *((int*) arg);
// //     minId = id - 1;
// //     //Wrap around for begining and end
// //     if (minId == -1){
// //        // minId = numPhilo - 1;
// //        minId = numPhilo;
// //        minId--;
// //     }

// //     //For as many times as they have to eat
// //     while (fatty < numNom) {
// //         //Lock 1 and 2
// //         printf("Philosopher %d Waiting...\n", id + 1);
// //         pthread_mutex_lock(&chops[id]);
// //         pthread_mutex_lock(&chops[minId]);
// //         fatty++;
// //         sleep(1);

// //        // printf("Philosopher %d Eating....\n", id + 1);
// //         printPhiloEating(id + 1);
// //         pthread_mutex_unlock(&chops[id]);
// //         pthread_mutex_unlock(&chops[minId]);
// //         //printf("Philosopher %d has eaten!\n", id + 1);
// //         printPhiloHasEaten(id + 1);

// //     }
// //     phioFed++;
// //     return NULL;
// // }

// // void printPhiloEating(int id){

// //     printf("Philosopher %d Eating....\n", id + 1);
// // }

// // void printPhiloHasEaten(int id){

// //      printf("Philosopher %d has eaten!\n", id + 1);
// // }

// int main(int argc, char* argv[]){

//     if(argc == 0){
//         printf("Incorrect Number of Arguments!\n");
//         printf("Please run again\n");
//         exit(0);
//     }
//     if(argc != 2){
//         printf("Insufficient args!\n");
//         printf("Please enter again!\n");
//         exit(0);
//     }

//     char *filename;
//     int check = 0;
//     filename = NULL;
//     filename = calloc(250, sizeof(char));
//     FILE* fp;

//     //strcpy(filename, argv[1]);
//     if(argv[1] != NULL){
//         strncpy(filename, argv[1], strlen(argv[1]) + 2);
//     }
//     if(filename != NULL){
//         fp = fopen(filename, "r");
//     }

//     if(fp == NULL){
//         printf("Unable to open file\n");
//         exit(0);
//     }

    
//         Queue *q1 = makeQueue(50, 0);
//         Queue *q2 = makeQueue(50, 0);
//         Queue *q3 = makeQueue(50, 0);
//         Queue *q4 = makeQueue(50, 0);
    

//    // Node *new = malloc(sizeof(Node));
//    Node *new = createNode();

//     while(fscanf(fp, "%s %d", &new->thread.pid, &new->thread.memUsg) == 2){
    
//         Node *temp1 = setNode(new);
//         Node *temp2 = setNode(new);
//         Node *temp3 = setNode(new);
//         Node *temp4 = setNode(new);

//         push(q1, temp1, 0);
//         push(q2, temp2, 0);
//         push(q3, temp3, 0);
//         push(q4, temp4, 0);
//     }
//     Queue *firstFit = q1;
//     Queue *bestFit = q2;
//     Queue *worstFit = q3;
//     Queue *nextFit = q4;
    
//     printfirstFit();
//     firstfit(firstFit);

//     printbestFit();
//     //bestfit(bestFit, 0);
//     worstfit(worstFit, 0);

//     printworstFit();
//     //worstfit(worstFit, 0);
//     bestfit(bestFit, 0);

//     printnextFit();
//     nextfit(nextFit);


//}

int main(int argc, char *argv[]){

    if(argc == 3){
        runq1(argc, argv);
    }
      else if(argc == 2){
          runq22(argc, argv);
      }
    return 0;
}