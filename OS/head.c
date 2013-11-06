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

char buff[1024], err_text[100] = "head: ";

//--------------------------------------------
// FUNCTION: file_open()
// This function opens the file for reading
// PARAMETERS:
// file_name - this parameter contains the name
// of the file
//--------------------------------------------
int file_open(char* file_name) {
	int open_descriptor = open(file_name, O_RDONLY, 0);
	return open_descriptor;
}

//--------------------------------------------
// FUNCTION: file_write()
// This function writes the first 10 lines of 
// the file in the standard output
// PARAMETERS:
// desc - this is the file descriptor
//--------------------------------------------
int file_write(desc) {
	
	int write_f, count, count2 = 0;
	char ch;

	count = 0;
	while(count < 10) {
		ch = buff[count2];
		if(ch == '\0') break;		
		write_f = write(STDOUT_FILENO, &ch, 1);
		if(ch == '\n') ++count;
		++count2;
	}
	return write_f;		
}

//--------------------------------------------
// FUNCTION: read_file()
// This function reads the file and puts it in
// the buffer
// PARAMETERS:
// desc - this is the file descriptor
// argv - this is the name of the file
//--------------------------------------------
int read_file(int desc, char* argv) {
	
	int read_bytes = read(desc, buff, 1024), i;

	if( read_bytes < 0 ) {
		return read_bytes;
	}

	buff[read_bytes] = '\0';//put the end of the string

	return read_bytes;
}

//--------------------------------------------
// FUNCTION: open_check()
// This function checks for errors after
// opening a file
// PARAMETERS:
// desc - file descriptor
// argv - name of the file
//--------------------------------------------
void open_check(int desc,char* argv) {
	if(desc < 0) { 
		strcat(err_text,"cannot open ");
		strcat(err_text, argv);
		strcat(err_text, " for reading");
		perror(err_text);
		exit(-1);
	}
}

//--------------------------------------------
// FUNCTION: read_check()
// This function checks for errors after
// reading the file
// PARAMETERS:
// bytes - bytes red 
// argv - name of the file
//--------------------------------------------
void read_check(int bytes, char* argv) {
	if(bytes < 0) {
		strcat(err_text,"fail to read ");
		strcat(err_text,argv);
		perror(err_text);
		exit(-2);
	}
}

//--------------------------------------------
// FUNCTION: write_check()
// This function checks for errors after
// writing 
// PARAMETERS:
// bytes - bytes written 
//--------------------------------------------
void write_check(int bytes) {
	if(bytes == -1) {
		perror("write()");
		exit(-3);
	}
}

int main(int argc, char* ARGV[]) {

	int file_count, descriptor, write_f, check_read, i;
	char file_name[100] = "==> ", buf;

	if(argc == 1) {
		for(i = 0; i < 10; ++i) {
			write_f = read(STDIN_FILENO, &buf, 100);
			write_check(write_f);
			write(STDOUT_FILENO, &buf, write_f);
			write_check(write_f);
		}
		return 0;
	}


	//read file for every filename in the command line
	for(file_count = 1; file_count < argc; ++file_count) {

		if(argc == 4 && *ARGV[2] == '-') {

			//write the name of the file
			write_check(write_f);

			strcat(file_name, ARGV[1]);
			strcat(file_name, " <==\n");

			write_f = write(STDOUT_FILENO, &file_name, 100);
			write_check(write_f); //write() error check

			descriptor = file_open(ARGV[1]);
			open_check(descriptor, ARGV[1]);

			check_read = read_file(descriptor, ARGV[file_count]);
			read_check(check_read,ARGV[file_count]);

			write_f = file_write(descriptor);
			write_check(write_f);

			buf = '\n';
			write_f = write(STDOUT_FILENO, &buf, 1);
			write_check(write_f);

			for( i = 0; i < strlen(file_name); ++i) 
				file_name[i] = '\0';

			write_f = write(STDOUT_FILENO, "==> ", 4);
			strcat(file_name, " standart input <==\n");
			write_f = write(STDOUT_FILENO, &file_name, 20);

			for(i = 0; i < 10; ++i) {
				write_f = read(STDIN_FILENO, &buf, 100);
				write(STDOUT_FILENO, &buf, write_f);
			}

			buf = '\n';
			write_f = write(STDOUT_FILENO, &buf, 1);
			write_check(write_f);

			for( i = 0; i < 50; ++i) 
				file_name[i] = '\0';

			descriptor = file_open(ARGV[3]);

			write_f = write(STDOUT_FILENO, "==> ", 4);
			write_check(write_f); //write() error check

			strcat(file_name, ARGV[3]);
			strcat(file_name, " <==\n");

			write_f = write(STDOUT_FILENO, &file_name, 100);
			write_check(write_f); //write() error check


			open_check(descriptor, ARGV[3]);
			read_file(descriptor, ARGV[file_count]);
			file_write(descriptor);

			return 0;
		}

		descriptor = file_open(ARGV[file_count]);
		open_check(descriptor, ARGV[file_count]); //open() error check

		check_read = read_file(descriptor, ARGV[file_count]);
		read_check(check_read,ARGV[file_count]); //read() error check
	
		for( i = 0; i < strlen(file_name); ++i) 
			file_name[i] = '\0';

		//print file
		if(argc > 2) {
			write_f = write(STDOUT_FILENO, "==> ", 4);
			write_check(write_f);

			strcat(file_name, ARGV[file_count]);

			strcat(file_name, " <==\n");
			write_f = write(STDOUT_FILENO, &file_name, 100);
			write_check(write_f);
		}

		write_f = file_write(descriptor);
		write_check(write_f);

		buf = '\n';

		//print new line
		if(file_count < argc - 1) {
			write_f = write(STDOUT_FILENO, &buf, 1);
			write_check(write_f);
		}

		//close() error check
		if(close(descriptor)) {
			perror("close()");
			return -4;
		}
	}
	return 0;
}
