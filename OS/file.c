#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

	int fd = open("file.c", O_RDONLY);
	if(fd == -1) {
		perror("open()");
		return -1;
	}

	char buffer[50000];
	int result = read(fd, buffer, 50000);

	if(result == -1) {
		perror("read() - main.c");
		return -2;
	}

	int	result1 = write(STDOUT_FILENO, buffer, result);

	if(result < 0) {
		perror("write() - main.c");
		return -3;

	}









	return 0;
}
