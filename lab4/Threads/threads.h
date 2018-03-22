/* This is where you implement the core solution.
   by <Name>, <Date>
*/
#include <pthread.h>
#define MAX_BUFFER_SIZE 100000
#define MAX_N_SIZE 100

extern int buffer[MAX_N_SIZE][MAX_BUFFER_SIZE];
/* other global variable declarations can go here */

typedef struct{
    pthread_t tid;
    struct timeval  startTime;
    struct timeval endTime;
    long int totalTime;
    int index;
    int* inputData;
    int workLoad;
}ThreadBox;

void BruteForceSort(int inputList[], int inputLength);
void BubbleSort(int inputList[], int inputLength);
void MergeSort(int *array, int left, int right);
void Merge(int *array, int left, int mid, int right);
void MergeAndOutputBuffer(char* outputFile);
void* BruteRunner(void* param);
void* BubbleRunner(void* param);
void* MergeRunner(void* param);
int SortingStats(ThreadBox* threads, int numThreads);


