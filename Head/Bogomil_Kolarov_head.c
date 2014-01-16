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

//--------------------------------------------
// FUNCTION: stdin_support()
// This function reads a line from stdin 
// and then writes it to stdout. This operations
// are repeating ten times 
//--------------------------------------------
int stdin_support() {
        int line_count = 0;
        char buffer[1];

        while(line_count < 10) {
                int read_bytes = read(STDIN_FILENO, buffer, 1);
				if(read_bytes == -1) {
					return -1;
				}
                int write_bytes = write(STDOUT_FILENO, buffer, read_bytes);        
				if(write_bytes == -1) {
					return -2;
				}
                if(*buffer == '\n' || *buffer == '\r' || *buffer == '\t') {
                        ++line_count;
                }
        }
	return 0;
}

//--------------------------------------------
// FUNCTION: file_open()
// This function reads opens a file
// and returns the file descriptor
// for the same file. 
// PARAMETERS:
// file_name - points to the name 
// of the file, that will be opened.
//--------------------------------------------
int file_open(char* file_name) {
        int file_descriptor = open(file_name, O_RDONLY);
        return file_descriptor;
}

//--------------------------------------------
// FUNCTION: print_header()
// This function prints the header on
// the screen.
// PARAMETERS:
// file_name - points to the name 
// that will be in header.
//--------------------------------------------
int print_header(char *file_name) {
        int write_check;
        char *header = (char*) malloc(sizeof(char)*(strlen(file_name) + 10));

        strcpy(header, "==> ");
        strcat(header, file_name);
        strcat(header, " <==\n\0");
        write_check = write(STDOUT_FILENO, header, strlen(header));

        free(header);

        return write_check;
}

//--------------------------------------------
// FUNCTION: print_file()
// This function prints the file
// on the screen.
// PARAMETERS:
// descriptor - a copy of the file
// descriptor, used to read from file.
//--------------------------------------------
int print_file(int descriptor) {
        int line_count = 0, read_bytes = 0;
        char buffer[1];

        while(line_count < 10) {
                read_bytes = read(descriptor, buffer, 1);
				if(read_bytes == -1) {
					printf("in if: ");
					return -3;
				}
                if(read_bytes == 0) break;

                int write_bytes = write(STDOUT_FILENO, buffer, read_bytes);
				if(write_bytes == -1) {
					return -4;
				}
				
                if(*buffer == '\n') {
                        ++line_count;
                }
        }
	return 0;
}

//--------------------------------------------
// FUNCTION: error_handle()
// This function is called when an error
// has occurred and handles it.
// PARAMETERS:
// err_num - this is the error code
// file_name - points to the name of the file
//--------------------------------------------
void error_handle(int err_num, char *file_name) {
	char* error_message = NULL;

	switch(err_num) { //Every error has it's own num. There is a message for every error.
		case 1: 
			error_message = (char*) malloc(sizeof(char)*(strlen(file_name)+48));
			strcpy(error_message, "Monkeys were unable to open \"");
			strcat(error_message, file_name);
			strcat(error_message, "\" for reading\n\0");
			break;
		case 2:
			error_message = (char*) malloc(sizeof(char)*(strlen(file_name)+35));
			strcpy(error_message, "Monkeys couldn't read from \"");
			strcat(error_message, file_name);
			strcat(error_message, "\"\n\0");
			break;
		case 3:
			error_message = (char*) malloc(sizeof(char)*(strlen(file_name)+40));
			strcpy(error_message, "Monkeys couldn't write \"");
			strcat(error_message, file_name);
			strcat(error_message, "\" to stdout\n\0");
			break;
		case 4:
			error_message = (char*) malloc(sizeof(char)*32);
			strcpy(error_message,"Reading from stdin - trolled\n\0");
			break;
		case 5:
			error_message = (char*) malloc(sizeof(char)*32);
			strcpy(error_message, "Writing to stdout - trolled\n\0");
			break;
	}
	perror(error_message);
	free(error_message);
}

int main(int argc, char *argv[]) {

        int line_count = 0, file_count, file, check;
        char buffer[1];

        if(argc == 1) {
                check = stdin_support();
				if(check == -1) {
					error_handle(4, "no_file"); //The function expects a second argument(name of file) but in this case there is no file.
				}
                return 0;
        } else {
                for(file_count = 1; file_count < argc; ++file_count) {
                        if(*argv[file_count] == '-') {
								if(argc > 2) {
                                	check = write(STDOUT_FILENO, "==> standart input <==\n", 23);
									if(check == -1) {
										error_handle(4, "no_file");
										continue;
									}
								}
                                check = stdin_support();
								if(check == -1) {
									error_handle(4, "no_file");
								} else
									if(check == -2) {
										error_handle(5, "no_file");
									}
                                continue;
                        }
                        file = file_open(argv[file_count]);
						if(file == -1) {
							error_handle(1, argv[file_count]);
							continue;
						}

                        if(argc > 2) {
                                check = print_header(argv[file_count]);
								if(check == -1) {
									error_handle(4, "no_file");
									continue;								
								}
                        }

                        check = print_file(file);
						if(check == -3) {
							error_handle(2, argv[file_count]);
							continue;
						} else
							if(check == -4) {
								error_handle(3, argv[file_count]);
								continue;
							}
                        close(file);
                }
        }

        return 0;
}
