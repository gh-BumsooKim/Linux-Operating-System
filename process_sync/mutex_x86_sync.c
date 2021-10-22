#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
 
#define BUFFER_SIZE 5

// global variable
int total_balance = 1000000;
int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

// 0 is not mutex, 1 is mutex
int mutex = 1;

void enter_region() {
	if (mutex == 1){
	    asm(
	        ".data\n"
	        "lock:\n"
	        ".byte 0\n"
	        ".text\n"
	        "_enter_region:\n"
	        "movb $1, %al\n" // move 1 to AL 
	        "xchgb lock,%al\n" 
	        "cmp $0, %al\n"
	        "jne _enter_region\n"
	    );
	}
}

void leave_region() {
	if (mutex == 1){
	    asm("movb $0, lock");
	}
}

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
	        enter_region();
	        //printf("f1 start its critical section\n");
	        critical_region_1(p);
	        //printf("f1 end its critical section\n");
	        leave_region();
    	}
    }
    pthread_exit(NULL);
}

static void* f2(void* p) {
	int i;
    for(i=0; i<10; i++) {
        puts("f2 wait for f1");
        
		if (count > 0){
	        enter_region();
	        //printf("f2 start its critical section\n");
	        critical_region_2(p);
	        //printf("f2 end its critical section\n");
	        leave_region();
    	}
    }
    pthread_exit(NULL);
}

int main() {
    int rc;
 
    pthread_t t1, t2;
 
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
    
    return 0;
}
