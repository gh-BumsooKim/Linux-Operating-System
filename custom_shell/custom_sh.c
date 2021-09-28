#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define EXIT "exit"

int main(){
	// process variable
	pid_t pid;
	int exit_code;

	// command variable
	char input[20];
	char *arg;		// temp arg for strtok
	char arg1[10];		// 1st arg
	char arg2[10] = "-l";	// 2nd arg

	while (TRUE){
		// STEP 0. input char
		printf("bummsookim-shell $ ");
		gets(input);

		// STEP 1-1. if input == "exit", then termination
		if (!strcmp(input, EXIT))
			break;

		// STEP 1-2. if input != "exit", then fork and execute
		//puts(input); // debug
		pid = fork();

		switch(pid){
		case -1:
			perror("fork failed");
			exit(1);
		case 0: // child process
			exit_code = 37;
			break;
		default: // parent process
			exit_code = 0;
			break;
		}

		// STEP 2-1. child process : execute command
		if (pid == 0) {
			arg = strtok(input, " ");
			if (arg != NULL)
				strcpy(arg1, arg); // arg1 == command

			arg = strtok(NULL, " ");
			if (arg != NULL)
				strcpy(arg2, arg); // arg2 == options

			execlp(arg1, arg1, arg2, NULL);

			exit(exit_code);
		}

		// STEP 2-2. parent proces : wait child process
		if (pid != 0) {
			int stat_val;
			pid_t child_pid;

			child_pid = wait(&stat_val);

			/*
			if (WIFEXITED(stat_val)) {
				printf("Child exited\n");
			}
			else
				printf("Child error exited");
			*/
		}
	}

	// STEP 3. termination
	exit(exit_code);
	//printf("custom shell was terminated\n");
}
