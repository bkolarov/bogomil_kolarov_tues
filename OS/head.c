//--------------------------------------------
// NAME: Bogomil Kolarov
// CLASS: 11a
// NUMBER: 5
// PROBLEM: #1
// FILE NAME: head.c
// FILE PURPOSE: realization of head program
//---------------------------------------------

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

char buff[1024];

//File open function
int file_open(char* file_name) {
		int open_descriptor = open(file_name, O_RDONLY, 0);
 return open_descriptor;
}

//File write function
int file_write(desc) {
	
	int write_f, count, count2 = 0;
	char ch;

	count = 0;
	while(count < 10) {
		ch = buff[count2];
		if(ch == '\0') break;		
		write(STDOUT_FILENO, &ch, 1);
		if(ch == '\n') ++count;
		++count2;
	}
	return write_f;		
}

//Read file function
int read_file(int desc, char* argv) {
	
	int read_bytes = read(desc, buff, 1024), i;

	if( read_bytes < 0 ) {
		return read_bytes;
	}

	buff[read_bytes] = '\0';//put the end of the string

	return read_bytes;
}

int main(int argc, char* ARGV[]) {

	int file_count, descriptor, write_f, check_read, i;
	char file_name[100] = "==> ";

	//read file for every filename in the command line
	for(file_count = 1; file_count < argc; ++file_count) {

		descriptor = file_open(ARGV[file_count]);

		if( descriptor < 0 ) {
			perror("open()"); //error check
			return -1;
		}

		check_read = read_file(descriptor, ARGV[file_count]);

		if(check_read < 0 ) { //error check
			perror("read()");
			return -2;
		}

		for( i = 0; i < strlen(file_name); ++i) file_name[i] = '\0';

		//print file
		if(argc > 2) {
			write(STDOUT_FILENO, "==> ", 4);
			strcat(file_name, ARGV[file_count]);
			strcat(file_name, " <==\n");
			write(STDOUT_FILENO, &file_name, 100);
		}
		write_f = file_write(descriptor);
		if(write_f == -1) {
			perror("write()");
			return -3;
		}
		if(close(descriptor)) { //error check
			perror("close()");
			return -4;
		}
	}
	return 0;
}
