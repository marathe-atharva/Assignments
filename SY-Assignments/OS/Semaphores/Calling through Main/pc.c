/**
 * - Standard Producer-Consumer Problem
 * - Author: Atharva Marathe
 * - Date: 15/04/2020
 * 
 * - This is a simple user-friendly program that demonstrates 
 *   Producer-Consumer problem.
 * 
 * - Compile: gcc -Wall -Werror -std=c99 -pthread pc.c queue.c -o pc
 * - Run: ./pc
 * - OR : ./makefile pc queue
 * 
 * - Input:
 *   - Number of producer and consumer threadds
 *   - Number of iterations
 * 
 * - Output: Demo of Production-consumtion cycle
 *  
 * - Limits/Known bugs: 
 *   - The datatype of sub-arrays in the structure is INT
 *   - The queue size isn't dynamically allocated (MAX_SIZE 100)
 * 
 * - Warnings:
 *   - 25 < Consumers < 35
 *   - 25 < Producers < 35
 *   - 50 < Consumers < 100
 * - [ USE THESE VALUES FOR BETTER DEMONSTARTION, OTHERWISE 
 *    ANY VALUES WOULD WORK JUST FINE! ] 
 **/


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "queue.h"
#define MAX_SIZE 100

int prodCount=0;
int consCount=0;

sem_t empty;
sem_t full;
sem_t mutex;

void *producer (void *args) {
    int item;
    if(!isFull()) {
        sem_wait(&empty);
        sem_wait(&mutex);
            item = enque();
            prodCount++;
            printf ("%02d produced\n", item);
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer (void *args) {
    int item;
    if(!isFull()) {
        sem_wait(&full);
        sem_wait(&mutex);
            item = deque();
            consCount++;
            printf ("%02d consumed\n", item);
        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}


int main (int argc, char *args[]) {

    int numP, numC, numIt, i, j;

    printf("Number of producers: ");
    scanf("%d", &numP);

    printf("Number of consumers: ");
    scanf("%d", &numC);
    
    printf("Number of iterations: ");
    scanf("%d", &numIt);

    pthread_t tid;

    sem_init(&empty, 0, MAX_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (i=0; i<numIt; i++) {
        for (j=0; j<numP; j++) {
            pthread_create(&tid, NULL, producer, NULL);
        }
        for (j=0; j<numC; j++) {
            pthread_create(&tid, NULL, consumer, NULL);
        }
    }

    printf("\nProductions: %d\nConsumtions: %d\n", prodCount, consCount);
    printf("Executed Succesfully!\n");
    return 0;
}