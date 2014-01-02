//---------------------------- 
//Name: Bogomil Kolarov
//Class:11a 
//Number: 5
//Problem: 2 
//File Name: shell.c 
//File Purpose: This is the source code file 
//for simple shell implementation program. 
//----------------------------
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>

//--------------------------------- 
//Function: parse_cmdline(const char* cmdline) 
//This function takes the input from stdin 
//and returns it as array of strings.
//If stdin is /bin/ls -l /usr/include
//the function will return ["/bin/ls","-l","/usr/include"]
//---------------------------------
char** parse_cmdline(const char* cmdline) {

	int count, word_count = 0;
	char** line_parsed = NULL;
	char *pch, *cmdline_copy = (char*)malloc(sizeof(char)*(strlen(cmdline)+1));
	strcpy(cmdline_copy, cmdline);

	pch = strtok(cmdline_copy," \n\t\r");

  	while (pch != NULL) {
		++word_count;		
    	pch = strtok(NULL, " \n\t\r");
  	}
	line_parsed = (char**)malloc((word_count+1)*sizeof(char*));
	count = 0;

	strcpy(cmdline_copy, cmdline);
	pch = strtok(cmdline_copy," \n\t\r");
  	while (pch != NULL) {		
		line_parsed[count] = (char*)malloc((strlen(pch) + 1)*sizeof(char));
		strcpy(line_parsed[count], pch);
		++count;
    	pch = strtok(NULL," \n\t\r");
  	}

	line_parsed[count] = NULL;
	free(cmdline_copy);
	return line_parsed;
}

int main() {

	int count = 0;
	size_t size;
	char* line = NULL;
	char** cmdline;

	while(1) {
		printf("$Monkey eats:< ");
		getline(&line, &size, stdin);
		cmdline = parse_cmdline(line);
		free(line);

		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");
			return -1;
		} else if(pid == 0) {
			struct stat _stat;
			stat(cmdline[0], &_stat);

			if(_stat.st_mode & S_IXUSR){	
				execvp(cmdline[0], cmdline);
			}else fprintf(stderr,"%s: Permission denied!\n",cmdline[0]);
				perror("");
		exit(1);
		}else {
			wait(NULL);
		}
		free(cmdline);
	}
	return 0;
}
