#include <stdio.h>
#include <unistd.h>

int main() {
	printf("1\n");
	execl("/bin/ls","/bin/ls", "-l", NULL);
	perror("");
	printf("2\n");


	return 0;
}
