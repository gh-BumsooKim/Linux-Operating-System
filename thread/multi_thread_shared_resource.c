#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define ITERATION 10

int gNumber = 0;
int status = 0;

int random_generation(){
	srand(time(NULL));
	return rand() % 100;
}

void *producer(void *arg){
	int random = 0;
	int p_sum = 0;

	for(int i=0; i<ITERATION; i++){
		if(status == 0){
			gNumber = random_generation();
			p_sum = p_sum + gNumber;

			//puts(gNumber);
			printf("Producer : %d\n", gNumber);
			status = 1;
		}
		else
			sleep(1);
	}
	pthread_exit((void *)p_sum);
}

void *consumer(void *arg){
	int s_sum = 0;

	for(int i=0; i<ITERATION; i++){
		if(status == 1){
			s_sum = s_sum + gNumber;

			printf("\tConsumer : %d\n", gNumber);
			status = 0;
		}
		else
			sleep(1);
	}
	pthread_exit((void *)s_sum);
}


int main(){
	int res_creation_p, res_creation_c;
	int res_join_p, res_join_c;
	pthread_t producer_thread, consumer_thread;
	void *result_t_p, *result_t_c;

	res_creation_p = pthread_create(&producer_thread, NULL, producer, NULL);
	res_creation_c = pthread_create(&consumer_thread, NULL, consumer, NULL);

	if (res_creation_p!=0 || res_creation_c!=0){
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}

	res_join_p = pthread_join(producer_thread, &result_t_p);
	res_join_c = pthread_join(consumer_thread, &result_t_c);

	if (res_join_p!=0 || res_join_c!=0){
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);
	}

	if ((int *)result_t_p == (int *)result_t_c){
		printf("Success with P : C = %d : %d\n", (int *)result_t_p, (int *)result_t_c);
	}
	else{
		printf("Fail with P : C = %d : %d\n", (int *)result_t_p, (int *)result_t_c);
	}

	exit(EXIT_SUCCESS);
}
