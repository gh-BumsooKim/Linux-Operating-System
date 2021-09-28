#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
        char input[10];
        char arg1[10];          // first arg
        char arg2[] = "-l";     // seconde arg
        char *arg;              // strtok pointer

        printf("exec system call function\n");

        gets(input);

        // first argument : command
        arg = strtok(input, " ");
        if (arg != NULL)
                strcpy(arg1, arg);

        // seconde argument : options
        arg = strtok(NULL, " ");
        if (arg != NULL)
                strcpy(arg2, arg);

        execlp(arg1, arg1, arg2, NULL);

        exit(0);
}
