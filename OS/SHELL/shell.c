//---------------------------- 
//Name: Bogomil Kolarov
//Class:11a 
//Number: 5
//Problem: 2 
//File Name: shell.c 
//File Purpose: This is the source code file 
//for simple shell implementation program. 
//----------------------------

/*
1.getline
2.parse it to a split function
2.1 split the line by spaces
2.2 return the new line in format ["word1","word2"]
*/

#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<string.h>

char** parse_cmdline(const char* cmdline) {

	int count, word_count = 0;
	char** line_parsed;
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
	pch = strtok (cmdline_copy," \n\t\r");
  	while (pch != NULL) {		
		line_parsed[count] = (char*)malloc((strlen(pch) + 1)*sizeof(char));
		strcpy(line_parsed[count], pch);
		++count;
    	pch = strtok (NULL," \n\t\r");
  	}
	line_parsed[count] = NULL;
	free(cmdline_copy);
	return line_parsed;
}

int main() {

	int count = 0;
	size_t size;
	char* line;
	char** cmdline;

	while(1) {
		getline(&line, &size, stdin);
		printf("marker\n");
		cmdline = parse_cmdline(line);
	

		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");
			return -1;
		} else if(pid == 0) {
			execv(cmdline[0], cmdline);			
		}else {
			wait(NULL);
		}
	}
	return 0;
}
