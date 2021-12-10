#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 1024

int main(){
	int fd;
	char *str_hello = "Hello, Vritual Buffer(SW Character Device)!";
	char buff[BUFF_SIZE];

	printf("Device driver test.\n");

	if ((fd=open("/dev/virtual_buffer", O_RDWR)) > 0){
		write(fd, str_hello, strlen(str_hello) + 1);
		printf("write to device: %s\n", str_hello);

		read(fd, buff, BUFF_SIZE);		
		printf("read from device: %s\n", buff);

		close(fd);
	} else
		printf("/dev/virtual_buffer open failed\n");
	return 0;
}

