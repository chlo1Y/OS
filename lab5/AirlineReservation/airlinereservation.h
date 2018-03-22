/* This is where you define the structs needed to 
 * solve this problem.  You can define constants, global
 *  variables, and function signatures here as well. 
 *  By Yuchen Wang & Zesun Yang, 2018.1.28
 */

#ifndef __AIRRES_H__
#define __AIRRES_H__

#include "./airplane.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

typedef struct {
    plane currentP;
    sem_t firstClass;
    sem_t coach;
    sem_t mutex;
} sharedMemory;

void createPlane(plane* p);
void executeChild(int number, FILE* output, int key);

#endif /* __AIRRES_H__ */