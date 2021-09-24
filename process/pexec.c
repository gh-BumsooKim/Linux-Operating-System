#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char *const ps_argv[] = {"ps", "-ax", 0};

	printf("exec system call function\n");

	//execl("bin/ps", "ps", "-ax", 0);
	execv("bin/ps", ps_argv);

	printf("Done\n");
	exit(0);
}
