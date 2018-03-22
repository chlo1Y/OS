/* Copyright 2016 Rose-Hulman */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>


/**
   In this system, there are 2 threads.  Thread one prints out A and
   C.  Thread two prints out B and D.  Use semaphores to ensure they
   always print A B C D.

   Use semaphores to enforce this constraint.
**/
sem_t s;
sem_t t;


void *threadOne(void *arg) {
  /*sleep(1); */
   /* just makes it obvious that it won't work without
                semaphores */
  while (1) {
    sem_wait(&s);
    printf("A\n");
    sem_post(&t);
    sem_wait(&s);
    printf("C\n");
    sem_post(&t);
    /*sem_wait(&s);*/
    /*sem_post(&t);*/
    return NULL;
  }
}

void *threadTwo(void *arg) {
  while (1) {
    sem_wait(&t);
    printf("B\n");
    sem_post(&s);
    sem_wait(&t);
    printf("D\n");
    sem_post(&s);
     return NULL;
  }
}

int main(int argc, char **argv) {
  pthread_t one, two;
  sem_init(&s, 0, 1);
  sem_init(&t, 0, 0);
  pthread_create(&one, NULL, threadOne, NULL);
  pthread_create(&two, NULL, threadTwo, NULL);
  pthread_join(one, NULL);
  pthread_join(two, NULL);

  printf("Everything finished.\n");
  return 0;
}

