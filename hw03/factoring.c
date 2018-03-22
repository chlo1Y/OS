/* Copyright 2016 Rose-Hulman Institute of Technology

Here is some code that factors in a super dumb way.  We won't be
attempting to improve the algorithm in this case (though that would be
the correct thing to do).

Modify code so that it starts the specified number of threads and
splits the computation between the threads.  You can be sure the max
allowed number of threads is 50.  Be sure your threads actually run in
paralell.

Your threads should each just print the factors they find, they don't
need to communicate the factors to the original thread.

ALSO - be sure to compile this code with -pthread

 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <math.h>
void *findFactor(void* box);
typedef struct {
  unsigned long long int start;
  unsigned long long int step;
  unsigned long long int target;
}TargetContainer;
int main(void) {
  /* you can ignore the linter warning about this */
  unsigned long long int target = 0;
  int numThreads;
  printf("Give a number to factor.\n");
  scanf("%llu", &target);

  printf("How many threads should I create?\n");
  scanf("%d", &numThreads);
  if (numThreads > 50 || numThreads < 1) {
    printf("Bad number of threads!\n");
    return 0;
  }
  int j = 0;
  TargetContainer pthreadData[50];
  pthread_t tid[50];
  int step = (target-1)/2/numThreads;
  int remain = ((target-1)/2)% numThreads;
  int startNum = 2;
  while ((startNum <= target/2) & (j < 50)) {
    pthreadData[j].start = startNum;
     pthreadData[j].target = target;
     pthreadData[j].step = step;
     startNum += step;
     if ((remain >0) & (startNum+ remain >= target/2)) {
       step+=remain;
       remain = 0;
     }
     pthread_create(&tid[j], NULL, findFactor, &pthreadData[j]);
     j++;
  }
  for (j = 0; j< numThreads; j++) {
    pthread_join(tid[j], NULL);
  }
  return 0;
}

void *findFactor(void* box) {
  unsigned long long int k;
  TargetContainer* box1 =(TargetContainer*) box;
  unsigned long long int start = (*box1).start;
  unsigned long long int step = (*box1).step;
  unsigned long long int target =(*box1).target;
  for (k = start; k < start+step; k++) {
    printf("testing %llu\n", k);
    if (target % k == 0) {
      printf("%llu is a factor\n", k);
    }
  }
  return 0;
}
