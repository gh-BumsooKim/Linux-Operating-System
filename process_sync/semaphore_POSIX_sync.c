#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
 
#define BUFFER_SIZE 5

// global variable
int total_balance = 1000000;
int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

//semaphore variable
sem_t bin_sem;

//P():try:wait()			atomic instruction
//
// 1) with busy-waiting
// 
// while S <= 0
//     no-op
// S--; 
//
// 2) without busy-waiting
//
// P(S) {
//     S--;
//     if S < 0
//         sleep-process

//V():increment:signal()	atomic instruction
//
// 1) with busy-waiting
//
// S++;
//
// 2) without busy-waiting
//
// V(S) {
//     S++;
//     if S <= 0
//         wakeup-process

//Process State
// running-process
// -> block() ->
// waiting-process
// -> wakeup() ->
// ready-process

void critical_region_1(char *p) { // producer
    int d = rand() % 10000;
    total_balance = total_balance - d;
    
    buffer[in] = d;
    in = (in + 1) % BUFFER_SIZE;
    count++;
    
    printf("\tf1 thread : %d\n", total_balance);
	usleep(d);
}

void critical_region_2(char *p) { // consumer
    int d;
    
    d = buffer[out];
	total_balance = total_balance + d;
	out = (out + 1) % BUFFER_SIZE;
    count--;
    
    printf("\tf2 thread : %d\n", total_balance);
	usleep(d);
}

static void* f1(void* p) {
	int i;
    for(i=0; i<10; i++) {
        puts("f1 wait for f2");
        
        if (count < BUFFER_SIZE){
	        sem_wait(&bin_sem);
	        //printf("f1 start its critical section\n");
	        critical_region_1(p);
	        //printf("f1 end its critical section\n");
	        sem_post(&bin_sem);
    	}
    }    
    pthread_exit(NULL);
}

static void* f2(void* p) {
	int i;
    for(i=0; i<10; i++) {
        puts("f2 wait for f1");
        
		if (count > 0){
	        sem_wait(&bin_sem);
	        //printf("f2 start its critical section\n");
	        critical_region_2(p);
	        //printf("f2 end its critical section\n");
	        sem_post(&bin_sem);
    	}
    }    
    pthread_exit(NULL);
}

int main() {
    int rc;
 
    pthread_t t1, t2;
 
 	sem_init(&bin_sem, 0, 1);
 
    rc = pthread_create(&t1, NULL, f1, "f1");
    if(rc != 0) {
        fprintf(stderr, "pthread f1 failed\n");
        return EXIT_FAILURE;
    }
 
    rc = pthread_create(&t2, NULL, f2, "f2");
    if(rc != 0) {
        fprintf(stderr, "pthread f2 failed\n");
        return EXIT_FAILURE;
    }
 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
 
    puts("All threads finished.");
    printf("Final total_balance : %d\n", total_balance);
    printf("Final count : %d", count);
    
    sem_destroy(&bin_sem);
    
    return 0;
}
