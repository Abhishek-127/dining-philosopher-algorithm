#ifndef Q2_H
#define Q2_H

typedef struct{
    char pid;
    int memUsg;
    int memSwap;
}Process;

typedef struct {
    Process thread;
    struct Node *prev;
} Node;

Node *createNode();
Node *setNode(Node *new);

void printfirstFit();

void printbestFit();

void printworstFit();


void printnextFit();



typedef struct{
    Node *head;
    Node *tail;
    int size;
    int limit;
} Queue;



Queue *createQueue(int limit,  int upperLimit);



Node* pop(Queue *pQueue);

void push(Queue *queue, Node *item,  int num);

Queue* makeQueue(int limit, int upperLimit);

void printMemStatus(Queue *memoryQ, double* cumulativeMem, char memory[128], double* totalPIDs, int *numProcesses, int* numHoles, int num);

void firstfit(Queue *q);

void bestfit(Queue *q, int a);

void worstfit(Queue *q, int a);

void nextfit(Queue *q);

void printMemory(char memory[128]);

void printFunction(double *numProcesses, double *numHoles, double *memUsg, double *cumulativeMem);

void fn2(double totalPIDs, double avgProcess, double avgHoles, double cumulativeMem);

void runq22(int argc, char *argv[]);


#endif