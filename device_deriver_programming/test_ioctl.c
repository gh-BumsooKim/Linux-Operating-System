#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

#define MY_IOCTL_NUMBER	100
#define MY_IOCTL_READ	_IOR(MY_IOCTL_NUMBER, 0, int)
#define MY_IOCTL_WRITE	_IOW(MY_IOCTL_NUMBER, 1, int)


int main(){
	int fd;
	int debug_flag = 0;

	if ((fd=open("/dev/virtual_buffer", O_RDWR)) > 0){
		ioctl(fd, MY_IOCTL_READ, &debug_flag);
		
		debug_flag = !debug_flag;

		ioctl(fd, MY_IOCTL_WRITE, &debug_flag);

		close(fd);
	} else
		printf("/dev/virtual_buffer open failed\n");
	return 0;
}

