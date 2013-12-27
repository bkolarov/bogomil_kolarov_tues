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
#include <stdlib.h>

void stdin_support() {
	int line_count = 0;
	char buffer[1];

	while(line_count < 10) {
		int read_bytes = read(STDIN_FILENO, buffer, 1);
		int write_bytes = write(STDOUT_FILENO, buffer, read_bytes);	

		if(*buffer == '\n' || *buffer == '\r' || *buffer == '\t') {
			++line_count;
		}
	}
}

int file_open(char* file_name) {
	int file_descriptor = open(file_name, O_RDONLY);
	return file_descriptor;
}

void print_file(int descriptor) {
	int line_count = 0;
	char buffer[1];

	while(line_count < 10) {
		int read_bytes = read(descriptor, buffer, 1);
		int write_bytes = write(STDOUT_FILENO, buffer, read_bytes);

		if(*buffer == '\n' || *buffer == '\r' || *buffer == '\t') {
			++line_count;
		}
	}
}

int main(int argc, char *argv[]) {

	int line_count = 0, file_count, file;
	char buffer[1];

	if(argc == 1) {
		stdin_support();
		return 0;
	} else {
		for(file_count = 1; file_count < argc; ++file_count) {
			if(*argv[file_count] == '-') {
				stdin_support();
				continue;
			}

			file = file_open(argv[file_count]);
			print_file(file);
			close(file);
		}
	}

	return 0;
}
