#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/timeb.h>

#include "q2.h"


void firstfit(Queue *q){
    
    char *memory = NULL;
    memory = calloc(128, sizeof(char));

    for(int i = 0; i < 128;i = i + 1){
        if(i >= 0){
            memory[i] = '0';
        }
    }

    Queue *memoryQ = makeQueue(50, 0);
   // int inserted = 1, numProcesses = 0, numHoles = 0;
   int inserted;
   inserted = 1;
   int numProcesses;
   numProcesses = 0;
   int numHoles;
   numHoles = 0;
   
    //double cumulativeMem = 0.0, totalPIDs = 0.0, avgProcess = 0.0, avgHoles = 0.0;
    double cumulativeMem;
    cumulativeMem = 0.0;
    double totalPIDs;
    totalPIDs = 0.0;
    double avgProcess;
    avgProcess = 0.0;
    double avgHoles;
    avgHoles = 0.0;

    //int flag, availMemory = 0;
    int flag;
    flag = 0;
    int availMemory;
    availMemory = 0;

    //Node *temp, *temp2;
    Node *temp = NULL;
    Node *temp2 = NULL;

    while(q->size != 0){
       
        numProcesses = numHoles = availMemory = flag = 0;

        if(inserted == 1 && numProcesses == 0){
            if(numHoles == 0){
                temp = pop(q);
            }
        }
        //int space = temp->thread.memUsg;
        int space;
        space = 0;
        space = temp->thread.memUsg;

        for(int i = 0; i < 128; i = i + 1){
            if(memory[i] == '0'){
                availMemory = availMemory + 1;
            }
            else{
                availMemory = 0;
            }

            if(availMemory >= space){
                for(int j = i; j > i-space; j = j -1){
                    if(j >= 0){
                        memory[j] = temp->thread.pid;
                    }
                }
                
                flag = 1;
                inserted = 1;
                if(flag == 1){
                    if(inserted == 1){
                        push(memoryQ, temp, flag);
                        printMemStatus(memoryQ, &cumulativeMem, memory, &totalPIDs, &numProcesses, &numHoles, 0);
                    }               
                }

                //avgProcess = ((avgProcess*(totalPIDs-1)) + numProcesses)/totalPIDs;
                avgProcess = ((avgProcess*(totalPIDs-1)) + numProcesses);
                avgProcess = avgProcess/totalPIDs;

                //avgHoles = ((avgHoles *(totalPIDs-1)) + numHoles)/totalPIDs;
                avgHoles = ((avgHoles *(totalPIDs-1)) + numHoles);
                avgHoles = avgHoles / totalPIDs;
                break;
            }
        }
        
        if(flag == 0) //No space
        {
            inserted = 0;
            temp2 = pop(memoryQ); //Pop process that's been on queue the longest
            for(int i = 0; i < 128; i = i + 1){
                if(memory[i] == temp2->thread.pid){
                    if(i >= 0){
                        memory[i] = '0';
                    }
                }
            }
            
            temp2->thread.memSwap = temp2->thread.memSwap + 1;

            if(temp2->thread.memSwap < 3){
                push(q, temp2, numProcesses);
            }
        }

    }

   // printf("**Total Loads: %.0lf, average #processes: %.2lf, average #holes: %.2lf, %%cumulativeMem: %.2lf**\n", totalPIDs, avgProcess, avgHoles, cumulativeMem);
    fn2(totalPIDs, avgProcess, avgHoles, cumulativeMem);
}

void bestfit(Queue *q, int a){
    char *memory;
    memory = calloc(128, sizeof(char));

    for(int i = 0; i < 128;i++){
        if(i >= 0){
            memory[i] = '0';
        }
    }

    Queue *memoryQ = makeQueue(50, 0);
    //int inserted = 1, holeIndex = 0, found = 0, numProcesses = 0, numHoles = 0;
    int inserted;
    inserted = 1;
    int holeIndex;
    holeIndex = 0;
    int found;
    found = 0;
    int numProcesses;
    numProcesses = 0;
    int numHoles;
    numHoles = 0;

    //double cumulativeMem = 0, totalPIDs = 0.0, avgProcess = 0.0, avgHoles = 0.0;
    double cumulativeMem;
    cumulativeMem = 0.0;
    double totalPIDs;
    totalPIDs = 0.0;
    double avgProcess;
    avgProcess = 0.0;
    double avgHoles;
    avgHoles = 0.0;

    //int flag, availMemory = 0, smallestSpace = 128, smallestIndex = 0;
    int flag;
    flag = 0;
    int availMemory;
    availMemory = 0;
    int smallestSpace;
    smallestSpace = 0;
    int smallestIndex;
    smallestIndex = 0;

   // Node *temp, *temp2;
   Node *temp;
   Node *temp2;
   
    while(q->size != 0){
       
        numProcesses = numHoles = holeIndex = availMemory = flag = found = 0;

        if(numProcesses >= 0 && numHoles >= 0){
            //smallestSpace = 128;
            smallestSpace = 127;
            smallestSpace++;
        }
        if(inserted == 1){
            temp = pop(q);
        }
        //int space = temp->thread.memUsg;
        int space;
        space = 0;
        space = temp->thread.memUsg;

        for(int i = 0; i < 128; i = i + 1){
            if(memory[i] == '0' && availMemory == 0){
                holeIndex = i;
                availMemory = availMemory + 1;
            }
            else if(memory[i] == '0'){
                availMemory = availMemory + 1;
            }
            else {
                found = 1;
                bool try = true;
                if(availMemory <= smallestSpace && availMemory >= space && try == true) { 
                    //flag = 1;
                    flag = 0;
                    flag = flag + 1;

                    //smallestIndex = holeIndex;
                    smallestIndex = 0;
                    smallestIndex += holeIndex;

                    //smallestSpace = availMemory;
                    smallestSpace = 0;
                    smallestSpace += availMemory;

                }
                availMemory = 0;
            }

            if(i == 127){
                bool try2 = true;
                if(availMemory <= smallestSpace && availMemory >= space && try2 == true){ 
                    flag = 1;
                    smallestIndex = holeIndex;
                    smallestSpace = availMemory;
                    availMemory = 0;
                }
            }
        }

        if(flag == 0){
            //inserted = 0;
            inserted = -1;
            inserted++;
            if(inserted == 0){
                temp2 = pop(memoryQ); 
            }
            
            for(int i = 0; i<128; i = i + 1){
                if(memory[i] == temp2->thread.pid){
                    if(i >= 0){
                        memory[i] = '0';
                    }
                }
            }
            //temp2->thread.memSwap++;
            temp2->thread.memSwap = temp2->thread.memSwap + 1;
            if(temp2->thread.memSwap < 3){
                push(q, temp2, numProcesses);
            }
        }
        else{
            for(int j = smallestIndex; j < smallestIndex+space; j = j + 1){
                if(j >= 0){
                    memory[j] = temp->thread.pid;
                }
            }
            //printMemory(memory);
            // flag = 1;
            // inserted = 1;
            flag = inserted = 1;
            push(memoryQ, temp, inserted);
            printMemStatus(memoryQ, &cumulativeMem, memory, &totalPIDs, &numProcesses, &numHoles, 0);
           // avgProcess = ((avgProcess * (totalPIDs-1)) + numProcesses)/totalPIDs;
           avgProcess = ((avgProcess * (totalPIDs-1)) + numProcesses);
           avgProcess = avgProcess / totalPIDs;

            //avgHoles = ((avgHoles * (totalPIDs-1)) + numHoles)/totalPIDs;
            avgHoles = ((avgHoles * (totalPIDs-1)) + numHoles);
            avgHoles = avgHoles / totalPIDs;

            
        }
    }

   // printf("**Total Loads: %.0lf, average #processes: %.2lf, average #holes: %.2lf, %%cumulativeMem: %.2lf**\n", totalPIDs, avgProcess, avgHoles, cumulativeMem);
    fn2(totalPIDs, avgProcess, avgHoles, cumulativeMem);
}

void worstfit(Queue *q, int a){
    ///char memory[128];
    char *memory;
    memory = NULL;
    memory = calloc(128, sizeof(char));

    for(int i = 0; i < 128;i = i  + 1){
        if(i >= 0){
            memory[i] = '0';
        }
    }

    Queue *memoryQ = makeQueue(50, 0);
    //int inserted = 1, holeIndex = 0, found = 0, numHoles = 0, numProcesses = 0;
    int inserted;
    inserted = 1;
    int holeIndex;
    holeIndex = 0;
    int found;
    found = 0;
    int numHoles;
    numHoles = 0;
    int numProcesses;
    numProcesses = 0;

    //double cumulativeMem = 0, totalPIDs = 0.0, avgProcess = 0.0, avgHoles = 0.0;
    double cumulativeMem;
    cumulativeMem = 0.0;
    double totalPIDs;
    totalPIDs = 0.0;
    double avgProcess;
    avgProcess = 0.0;
    double avgHoles;
    avgHoles = 0.0;

    //int flag, availMemory = 0, largestSpace, largestIndex = 0;
    int flag;
    flag = 0;
    int availMemory;
    availMemory = 0;
    int largestSpace;
    largestSpace = 0;
    int largestIndex;
    largestIndex = 0;

   // Node *temp, *temp2;
   Node *temp = NULL;
   Node *temp2 = NULL;

    while(q->size != 0){
        
        numProcesses = numHoles = holeIndex = availMemory = flag = found = largestSpace = 0;
        if(inserted == 1 && numProcesses == 0){
            if(holeIndex == 0){
                temp = pop(q);
            }
        }
        //int space = temp->thread.memUsg;
        int space;
        space = 0;
        space = temp->thread.memUsg;

        for(int i = 0; i < 128; i = i + 1){
            if(memory[i] == '0' && availMemory == 0){
                holeIndex = i;
                availMemory = availMemory +  1;
            }
            else if(memory[i] == '0'){
                availMemory = availMemory + 1;
            }
            else {
                found = 1;
                bool try = true;
                if(availMemory > largestSpace && availMemory >= space && try == true) { 
                    
                    flag = 1;
                    largestIndex = holeIndex;
                    largestSpace = availMemory;
                }
                availMemory = 0;
            }

            if(i == 127){
                bool try2 = true;
                if(availMemory > largestSpace && availMemory >= space && try2 == true){ 
                    //flag = 1;
                    flag = 0;
                    flag++;
                    //largestIndex = holeIndex;
                    largestIndex = 0;
                    largestIndex = largestIndex + holeIndex;

                    //largestSpace = availMemory;
                    largestSpace = 0;
                    largestSpace = largestSpace +availMemory;
                    availMemory = -1;
                    availMemory++;
                }
            }
        }

        if(flag == 0) {
            inserted = 0;
            temp2 = pop(memoryQ); 
            for(int i = 0; i < 128; i = i + 1){
                if(memory[i] == temp2->thread.pid){
                    memory[i] = '0';
                }
            }
            //temp2->thread.memSwap++;
            temp2->thread.memSwap = temp2->thread.memSwap + 1;
            if(temp2->thread.memSwap < 3){
                push(q, temp2, numProcesses);
            }
        }
        else {
            for(int j = largestIndex; j < largestIndex+space; j = j + 1){
                if(j >= 0){
                    memory[j] = temp->thread.pid;
                }
            }
            //printMemory(memory);
            // flag = 1;
            // inserted = 1;
            flag = inserted = 1;
            push(memoryQ, temp, numProcesses);
            printMemStatus(memoryQ, &cumulativeMem, memory, &totalPIDs, &numProcesses, &numHoles, 0);
            //avgProcess = ((avgProcess * (totalPIDs-1)) +numProcesses)/totalPIDs;
            avgProcess = ((avgProcess * (totalPIDs-1)) +numProcesses);
            avgProcess = avgProcess / totalPIDs;

            //avgHoles = ((avgHoles * (totalPIDs-1)) +numHoles)/totalPIDs;
            avgHoles = ((avgHoles * (totalPIDs-1)) +numHoles);
            avgHoles = avgHoles / totalPIDs;
        }
    }
    //printf("**Total Loads: %.0lf, average #processes: %.2lf, average #holes: %.2lf, %%cumulativeMem: %.2lf**\n", totalPIDs, avgProcess, avgHoles, cumulativeMem);
    fn2(totalPIDs, avgProcess, avgHoles, cumulativeMem);
}

void nextfit(Queue *q){
    //char memory[128];
    char *memory;
    memory = NULL;
    memory  = calloc(128, sizeof(char));

    for(int i = 0; i < 128;i = i + 1){
        if(i >= 0){
            memory[i] = '0';
        }
    }

    Queue *memoryQ = makeQueue(50, 0);

    //int inserted = 1, numProcesses = 0, numHoles = 0, lastIndex = 0;
    int inserted;
    inserted = 1;
    int numProcesses;
    numProcesses = 0;
    int numHoles;
    numHoles = 0;
    int lastIndex;
    lastIndex = 0;

    //double cumulativeMem = 0.0, totalPIDs = 0.0, avgProcess = 0.0, avgHoles = 0.0;
    double cumulativeMem;
    cumulativeMem = 0.0;
    double totalPIDs;
    totalPIDs = 0.0;
    double avgProcess;
    avgProcess  = 0.0;
    double avgHoles;
    avgHoles = 0.0;

    //int flag, availMemory = 0;
    int flag;
    flag = 0;
    int availMemory;
    availMemory = 0;

    //Node *temp, *temp2;
    Node *temp;
    Node *temp2;
    while(q->size != 0){
       
        numProcesses = numHoles = availMemory = flag = lastIndex = 0;
        if(inserted == 1 && q->size != 0){
            temp = pop(q);
        }
        //int space = temp->thread.memUsg;
        int space = 0;
        space = temp->thread.memUsg;

        ///int i = lastIndex;
        int i = 0;
        i = lastIndex;

        while(i < 128){
            
            if(memory[i] == '0'){

                availMemory = availMemory + 1;
            }
            else{
                availMemory = 0;
            }

            if(availMemory >= space){
                for(int j = i; j > i-space; j = j - 1) {
                    if(j >= 0){
                        memory[j] = temp->thread.pid;
                    }
                }
               bool check = true;
                flag = inserted = 1;
                lastIndex = i;
                if(check == true){
                    push(memoryQ, temp, 10);
                    printMemStatus(memoryQ, &cumulativeMem, memory, &totalPIDs, &numProcesses, &numHoles, 0);
                }
                
                avgProcess = ((avgProcess*(totalPIDs-1)) + numProcesses);
                avgProcess++;
                avgProcess--;
                avgProcess = avgProcess / totalPIDs;

                //avgHoles = ((avgHoles *(totalPIDs-1)) + numHoles)/totalPIDs;
                avgHoles = ((avgHoles *(totalPIDs-1)) + numHoles);
                avgHoles = avgHoles/totalPIDs;
                break;
            }
            i = i + 1;
        }
        if(flag == 0){
            inserted = 0;
            temp2 = pop(memoryQ); 
            for(int i = 0; i < 128; i = i + 1){
                if(memory[i] == temp2->thread.pid){
                    if(i >=  0){
                        memory[i] = '0';
                    }
                }
            }
            //temp2->thread.memSwap++;
            temp2->thread.memSwap = temp2->thread.memSwap + 1;

            if(temp2->thread.memSwap < 3){
                push(q, temp2, 5);
            }
        }
    }
    if(avgProcess >= 0){
        //printf("**Total Loads: %.0lf, average #processes: %.2lf, average #holes: %.2lf, %%cumulativeMem: %.2lf**\n", totalPIDs, avgProcess, avgHoles, cumulativeMem);
        fn2(totalPIDs, avgProcess, avgHoles, cumulativeMem);
    }
}

void printMemStatus(Queue *memoryQ, double* cumulativeMem, char memory[128], double* totalPIDs, int *numProcesses, int *numHoles, int num){

    int used;
    used = 0;
    Node  *head = NULL;
    if(used == 0){
        head = memoryQ->head;
    }
    else{
        head = memoryQ->head;
    }
    while(head != NULL){

        head = (Node*)(head->prev);
        //*numProcesses+=1;
        *numProcesses = *numProcesses + 1;
    }
    for(int i = 0; i < 127; i = i + 1) {
        if(memory[i] == '0' && memory[i+1] != '0'){
            //*numHoles+=1;
            if(i >= 0){
                *numHoles = *numHoles + 1;
            }
        }

        if(memory[i] != '0'){
            if(i >= 0){
                used = used + 1;
            }
        }
    }

    if(memory[127] != '0'){
        used = used + 1;
    }
    else{
        //*numHoles += 1;
        *numHoles  = *numHoles + 1;
    }

    //double memUsg = (double)used/128 * 100;
    double memUsg;
    memUsg = 0;
    memUsg = (double)used/128 * 100;

    //*cumulativeMem = ((*cumulativeMem * *totalPIDs) + memUsg)/ (*totalPIDs+1);
    *cumulativeMem = ((*cumulativeMem * *totalPIDs) + memUsg);
    *cumulativeMem = *cumulativeMem/(*totalPIDs + 1);

    //*totalPIDs += 1;
    *totalPIDs = *totalPIDs + 1;

    printf("PID Loaded, #processes = %d, #holes %d, %%memusage = %.2lf, cumulative %%mem = %.2lf\n", *numProcesses, *numHoles, memUsg, *cumulativeMem);

}


Queue *createQueue(int limit, int upperLimit){
    Queue *q = calloc(1, sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    q->limit = limit;
    return q;
}

void printMemory(char memory[128]){
    for(int i = 0; i<128; i = i + 1){
        if(i >= 0){
            printf("%c", memory[i]);
        }
    }
}


Queue* makeQueue(int limit, int upperLimit) {

    if(limit <= 0){
        limit = 65535;
    }
    Queue *queue = createQueue(limit, 0);

    return queue;
}

void push(Queue *queue, Node *item, int num) {
    
    bool check = false;
    if(1){
        check = true;
    }
    if ((queue == NULL) || (item == NULL) || check == false){
        return;
    }
    
    if(check == true){
        if(queue->size >= queue->limit){
            return;
        }
    }
    

    item->prev = NULL;
    if (queue->size == 0 && check == true){

        //queue->head = item;
        queue->head = NULL;
        if(queue->head == NULL){
            queue->head = item;
        }
        else{
            queue->head = item;
        }

        //queue->tail = item;
        queue->tail = NULL;
        if(queue->tail == NULL){
            queue->tail = item;
        }
        else{
            queue->tail = item;
        }

    } 
    else {

        queue->tail->prev = item;
        queue->tail = item;
    }
    queue->size = queue->size + 1;
}

Node* pop(Queue *queue){
    /*the queue is empty or bad param*/
    Node *head;
    head  = NULL;

    if (queue->size == 0){
        return NULL;
    }
    else{

        //head = queue->head;
        head = NULL;
        if(head == NULL){ 
            head = queue->head;
        }
        
        queue->head = ((Node*)(queue->head)->prev);

        //queue->size = queue->size - 1;
        queue->size = queue->size;
        queue->size--;

        return head;
    }
}

Node *createNode(){
    Node *n = calloc(1, sizeof(Node));

    return n;
}

Node *setNode(Node *new){

    Node *node = calloc(1, sizeof(Node) + 1);
    if(new != NULL){
        //node->thread.pid = new->thread.pid;
        node->thread.pid = 0;
        node->thread.pid = new->thread.pid;

        //node->thread.memUsg = new->thread.memUsg;
        node->thread.memUsg = 0;
        node->thread.memUsg = new->thread.memUsg;

        node->thread.memSwap = 0;
    }
    return node;
}

void printfirstFit(){

    printf("********************\n");
    printf("*     FIRST FIT    *\n");
    printf("********************\n");
}

void printbestFit(){

    printf("********************\n");
    printf("*     BEST FIT     *\n");
    printf("********************\n");
}

void printworstFit(){

    printf("********************\n");
    printf("*     WORST FIT    *\n");
    printf("********************\n");
}

void printnextFit(){

    printf("********************\n");
    printf("*     NEXT FIT     *\n");
    printf("********************\n");
}

void printFunction(double *numProcesses, double *numHoles, double *memUsg, double *cumulativeMem){

}

void fn2(double totalPIDs, double avgProcess, double avgHoles, double cumulativeMem){
    printf("**Total Loads: %.0lf, average #processes: %.2lf, average #holes: %.2lf, %%cumulativeMem: %.2lf**\n", totalPIDs, avgProcess, avgHoles, cumulativeMem);
}

void runq22(int argc, char *argv[]){

    if(argc == 0){
        printf("Incorrect Number of Arguments!\n");
        printf("Please run again\n");
        exit(0);
    }
    if(argc != 2){
        printf("Insufficient args!\n");
        printf("Please enter again!\n");
        exit(0);
    }

    char *filename;
    //int check = 0;
    filename = NULL;
    filename = calloc(250, sizeof(char));
    FILE* fp;

    //strcpy(filename, argv[1]);
    if(argv[1] != NULL){
        strncpy(filename, argv[1], strlen(argv[1]) + 2);
    }
    if(filename != NULL){
        fp = fopen(filename, "r");
    }

    if(fp == NULL){
        printf("Unable to open file\n");
        exit(0);
    }

    
        Queue *q1 = makeQueue(50, 0);
        Queue *q2 = makeQueue(50, 0);
        Queue *q3 = makeQueue(50, 0);
        Queue *q4 = makeQueue(50, 0);
    

   // Node *new = malloc(sizeof(Node));
   Node *new = createNode();

    while(fscanf(fp, "%s %d", &new->thread.pid, &new->thread.memUsg) == 2){
    
        Node *temp1 = setNode(new);
        Node *temp2 = setNode(new);
        Node *temp3 = setNode(new);
        Node *temp4 = setNode(new);

        push(q1, temp1, 0);
        push(q2, temp2, 0);
        push(q3, temp3, 0);
        push(q4, temp4, 0);
    }
    Queue *firstFit = q1;
    Queue *bestFit = q2;
    Queue *worstFit = q3;
    Queue *nextFit = q4;
    
    printfirstFit();
    firstfit(firstFit);

    printbestFit();
    //bestfit(bestFit, 0);
    worstfit(worstFit, 0);

    printworstFit();
    //worstfit(worstFit, 0);
    bestfit(bestFit, 0);

    printnextFit();
    nextfit(nextFit);

}