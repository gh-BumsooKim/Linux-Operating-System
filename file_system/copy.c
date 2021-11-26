#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define BUF_SIZE 1024

int statType(struct stat* buf);

void file2file(char* argv1, char* argv2);

void file2dir(char* argv1, char* argv2);


int main(int argc, char **argv){

	if (argc < 3){
		write(2, "Usage : copy file1 file2\n", 25);
		return -1;
	}

	struct stat argv1;
	struct stat argv2;

	lstat(argv[1], &argv1);
	lstat(argv[2], &argv2);

	printf("%d, %d", statType(&argv1), statType(&argv2)); // debug

	if (statType(&argv1) == 0 && statType(&argv2) == -1){
		if (strchr(argv[2], '.'))
			// file2file
			file2file(argv[1], argv[2]);
		else
			// file2dir
			file2dir(argv[1], argv[2]);
	}
	else if (statType(&argv1) != 0)
		// dir2file
		perror("Error : dir to file is not supported");

	return 0;
}


int statType(struct stat * buf){
	if (S_ISDIR(buf->st_mode))
		return 1;
	else if (S_ISREG(buf->st_mode))
		return 0;
	else
		return -1;
}

void file2file(char* argv1, char* argv2){
	int in, out, n;
	char buf[BUF_SIZE];

	if ((in = open(argv1, O_RDONLY)) < 0){
		perror("file open error");
		exit(1);
	}

	if ((out = open(argv2, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0){
		perror("file open error");
		exit(1);
	}

	while ((n = read(in, buf, sizeof(buf))) > 0){
		write(out, buf, n);
	}

	close(in);
	close(out);
}

void file2dir(char* argv1, char* argv2){
	int in, out, n;
	char buf[BUF_SIZE];

	if ((in = open(argv1, O_RDONLY)) < 0){
		perror("file open error");
		exit(1);
	}

	char path[BUF_SIZE];

	mkdir(argv2, 0777);

	strcat(path, argv2);
	strcat(path, "/");
	strcat(path, argv1);

	if ((out = open(path, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0){
		perror("file open error");
		exit(1);
	}

	while ((n = read(in, buf, sizeof(buf))) > 0){
		write(out, buf, n);
	}

	close(in);
	close(out);
}
