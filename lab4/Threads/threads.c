/* This is where you implement the core solution.
   b Zesun Yang & Yuchen Wang 
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "./threads.h"

int buffer[MAX_N_SIZE][MAX_BUFFER_SIZE];
int n;
/* other global variable instantiations can go here */

/* Uses a brute force method of sorting the input list. */

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("not enough argument\n");
    exit(-1);
  }
  FILE *inputFile = fopen(argv[2], "r");
  int threadNum = atoi(argv[1]);
  n = threadNum;
  if (inputFile == NULL) {
    return 0;
  }
  int count = 0;
  int initLine = 100;
  int* inputData = (int*) malloc(initLine* sizeof(int));
  while (!feof(inputFile)) {
    if (initLine == count) {
      initLine = initLine* 2;
      inputData = realloc(inputData, initLine * sizeof(int));
    }
    fscanf(inputFile, "%d", &(inputData[count]));
    count++;
  }

  int i;
  ThreadBox threads[1000];
  int workLoad = count /n;
  for (i = 0; i < n; i++) {
    threads[i].inputData = (int*) malloc(workLoad * sizeof(int));
    threads[i].inputData = &(inputData[i*workLoad]);
    threads[i].workLoad = workLoad;
    threads[i].index = i+1;
    gettimeofday(&(threads[i].startTime), NULL);
    if (i < threadNum / 3) {
      pthread_create(&(threads[i].tid), NULL, BruteRunner, &threads[i]);
    } else if ((i>= threadNum/3)  && (i < (2*threadNum/3))) {
      pthread_create(&(threads[i].tid), NULL, BubbleRunner, &threads[i]);
    } else {
      pthread_create(&(threads[i].tid), NULL, MergeRunner, &threads[i]);
    }
  }

  for (i = 0; i < threadNum; i++) {
    memcpy(buffer[i], threads[i].inputData, workLoad);
    pthread_join(threads[i].tid, NULL);
  }
  SortingStats(threads, threadNum);
  char *output = argv[3];
  MergeAndOutputBuffer(output);
  fclose(inputFile);
  return 0;
}

int SortingStats(ThreadBox* threads, int numThreads) {
  int bruteForceMin = 99999, bubbleMin = 99999, mergeMin = 99999;
  int bruteForceMax = 0, bubbleMax = 0, mergeMax = 0;
  int bruteForceTotal = 0, bubbleTotal = 0, mergeTotal = 0;
  int numBruteForceThread = 0, numBubbleThread = 0, numMergeThread = 0;
  int i;
  int sortTime;
  for (i = 0; i < numThreads; i++) {
    sortTime = threads[i].totalTime;
    if (i < numThreads/3) {
      if (sortTime < bruteForceMin) {
        bruteForceMin = sortTime;
      }
      if (sortTime > bruteForceMax) {
        bruteForceMax = sortTime;
      }
      bruteForceTotal = bruteForceTotal + sortTime;
      numBruteForceThread++;
    } else if ((i < 2 * numThreads /3) && (i >= numThreads/3)) {
      if (sortTime < bubbleMin) {
        bubbleMin = sortTime;
      }
      if (sortTime > bubbleMax) {
        bubbleMax = sortTime;
      }
      bubbleTotal = bubbleTotal + sortTime;
      numBubbleThread++;
    } else {
      if (sortTime < mergeMin) {
        mergeMin = sortTime;
      }
      if (sortTime > mergeMax) {
        mergeMax = sortTime;
      }
      mergeTotal = mergeTotal +sortTime;
      numMergeThread++;
    }
  }
  printf("Brute Force Time: min: %d us, max: %d us, mean: %d us\n",
    bruteForceMin, bruteForceMax, bruteForceTotal/numBruteForceThread);
  printf("Bubble Sort Time: min: %d us, max: %d us, mean: %d us \n",
    bubbleMin, bubbleMax, bubbleTotal/numBubbleThread);
  printf("Merge Sort Time: min: %d us, max: %d us, mean: %d us\n",
    mergeMin, mergeMax, mergeTotal/numMergeThread);
  return 0;
}

void BruteForceSort(int inputList[], int inputLength) {
  int i, j, temp;
  for (i = 0; i < inputLength; i++) {
    for (j = i+1; j < inputLength; j++) {
      if (inputList[j] < inputList[i]) {
        temp = inputList[j];
        inputList[j] = inputList[i];
        inputList[i] = temp;
      }
    }
  }
}
void* BruteRunner(void* param) {
  ThreadBox* data = (ThreadBox*) param;
  BruteForceSort((*data).inputData, (*data).workLoad);
  gettimeofday(&((*data).endTime), NULL);
  (*data).totalTime = (*data).endTime.tv_usec-(*data).startTime.tv_usec;
  printf("finished thread %d in %ld  us\n", (*data).index, (*data).totalTime);
  pthread_exit(0);
}
/* Uses the bubble sort method of sorting the input list. */
void BubbleSort(int inputList[], int inputLength) {
  char sorted = 0;
  int i, temp;
  while (!sorted) {
    sorted = 1;
    for (i = 1; i < inputLength; i++) {
      if (inputList[i] < inputList[i-1]) {
        sorted = 0;
        temp = inputList[i-1];
        inputList[i-1] = inputList[i];
        inputList[i] = temp;
      }
    }
  }
}
void* BubbleRunner(void* param) {
  ThreadBox* data = (ThreadBox*) param;
  BubbleSort((*data).inputData, (*data).workLoad);
  gettimeofday(&((*data).endTime), NULL);
  (*data).totalTime = (*data).endTime.tv_usec-(*data).startTime.tv_usec;
  printf("finished thread %d  in %ld us\n", (*data).index, (*data).totalTime);
  pthread_exit(0);
}

/* Merges two arrays.  Instead of having two arrays as input, it
 * merges positions in the overall array by reording data.  This saves
 * space. */
void Merge(int *array, int left, int mid, int right) {
  int tempArray[MAX_BUFFER_SIZE];
  int pos = 0, lpos = left, rpos = mid + 1;
  while (lpos <= mid && rpos <= right) {
    if (array[lpos] < array[rpos]) {
      tempArray[pos++] = array[lpos++];
    } else {
      tempArray[pos++] = array[rpos++];
    }
  }
  while (lpos <= mid)  tempArray[pos++] = array[lpos++];
  while (rpos <= right)tempArray[pos++] = array[rpos++];
  int iter;
  for (iter = 0; iter < pos; iter++) {
    array[iter+left] = tempArray[iter];
  }
  return;
}

/* Divides an array into halfs to merge together in order. */
void MergeSort(int *array, int left, int right) {
  int mid = (left+right)/2;
  if (left < right) {
    MergeSort(array, left, mid);
    MergeSort(array, mid+1, right);
    Merge(array, left, mid, right);
  }
}

void* MergeRunner(void* param) {
  ThreadBox* data = (ThreadBox*) param;
  MergeSort((*data).inputData, (*data).workLoad/2, (*data).workLoad/2);
  gettimeofday(&((*data).endTime), NULL);
  (*data).totalTime = (*data).endTime.tv_usec-(*data).startTime.tv_usec;
  printf("finished thread %d in %ld us\n", (*data).index, (*data).totalTime);
  pthread_exit(0);
}

/* Merges the sorted files into an output file using the two
 * dimensional output buffer */
void MergeAndOutputBuffer(char* outputFile) {
  FILE *outFile = fopen(outputFile, "w");
  if (outFile == NULL) {
    fprintf(stderr, "Unable to open the file %s\n", outputFile);
    exit(2);
  }
  int i;
  __int64_t j;
  int indexes[MAX_N_SIZE], maxIndexes[MAX_N_SIZE];
  for (i = 0; i < n; i++) {
    for (j = 0; buffer[i][j] > 0; j++) {
    }
    maxIndexes[i] = j;
    indexes[i] = 0;
  }
  int smallIndex;
  j = 0;
  while (1) {
    smallIndex = -1;
    for (i = 0; i < n; i++) {
      if (indexes[i] < maxIndexes[i]) {
        smallIndex = i;
        break;
      }
    }
    if (smallIndex == -1) {
      break;
    }
    for (i = 1; i < n; i++) {
      if ((indexes[i] < maxIndexes[i]) &&
          (buffer[i][indexes[i]] < buffer[smallIndex][indexes[smallIndex]])) {
        smallIndex = i;
      }
    }
    fprintf(outFile, "%d\n", buffer[smallIndex][indexes[smallIndex]]);
    fflush(outFile);
    indexes[smallIndex]++;
    j++;
  }
  fclose(outFile);
}






