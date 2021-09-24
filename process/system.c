#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("system function call\n");

	system("ps -ax");

	printf("Done\n");
	exit(0);
}
