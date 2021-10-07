#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREAD 10

void *thread_f(void *t_id){
	printf("\trunning Thread Number : %d\n", (int *)t_id);
	pthread_exit(0);
}

int main(){
	pthread_t threads[N_THREAD];
	int status, res, i;
	void *thread_result;

	for(i=0; i<N_THREAD; i++){
		printf("Starting Thread Number : %d\n", i);
		status = pthread_create(&threads[i], NULL, thread_f, (void *)i);

		if(status != 0){
			//printf("Exit with Thread Error\n");
			perror("Exit with Thread Creation Error\n");
			exit(EXIT_FAILURE);
		}
	}

	for(i=0; i<N_THREAD; i++){
		res = pthread_join(threads[i], &thread_result);
	}

	exit(0);
}
