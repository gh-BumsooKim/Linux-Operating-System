#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define EXIT "exit"

int main(){
	char input[100];
	pid_t pid;
	int exit_code;

	while (TRUE){
		// STEP 0, input char
		printf("bummsookim-shell $ ");
		gets(input);

		// STEP 1-1, if input == "exit", then termination
		if (!strcmp(input, EXIT))
			break;

		// STEP 1-2, if input != "exit", then fork and execute command
		puts(input); // debug
		pid = fork();

		switch(pid){
		case -1:
			perror("fork failed");
			exit(1);
		case 0; // child process
			exit_code = 37;
			break;
		default: // parent process
			exit_code = 0;
			break;
		}

		if (pid != 0) {
			int stat_val;
			pid_t child_pid;

			child_pid = wait(&stat_val);
		}

	}

	printf("custom shell was terminated\n");
}
