#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80 //the maximun length command 

int main(void){

	char * args[MAX_LINE/2 + 1]; //command line arguments 
	int should_run = 1; //flag to determine when to exit program 
	
	char buffer[MAX_LINE]; //buffer for a user input
	int arg_index = 0; 
	
	pid_t pid; 
	while(should_run){
		printf("osh>"); 
		fflush(stdout); 

		//after reading user input, 
		//(1) fork a child process using fork()
		//(2) the child process will invoke execvp() 
		//(3) if command included &, parent will invoke wait() 
		
		//This scanf will accept all characters except \n
		scanf("%[^\n]", buffer);
		int length = strlen(buffer);
		printf("length : %d\n", length); 
		//make the buffer string into an array of char pointers. 
		int start = 0; 
		
		for(int i = 0; i < length; i++){
			printf("buffer[%d] = %d\n", i, buffer[i]);
			
			if(buffer[i] == 32 || buffer[i] == 0){
				int j = start;
				int str_length = i - j + 1;
				printf("string length : %d\n", str_length);  
				char * sub_buffer = calloc(str_length, sizeof(char));
				for(int k = 0; j < i; j++){
					sub_buffer[k] = buffer[j];
					printf("sub_buffer[%d] = %c\n", k, sub_buffer[k]);
					k++; 
				}
				strcpy(args[arg_index++], sub_buffer); 
				start = i + 1;
				free(sub_buffer); 
			}
		}
			
		for(int i = 0; i < arg_index; i++){	
			printf("argument %d => %s\n", i, args[i]);
		}
		
		pid = fork(); 
		if(pid < 0){
			fprintf(stderr, "Fork Failed!"); 
			exit(0); 
		}
		else if(pid == 0){
			//child process 
			execvp(args[0], args);
		}
		else{
			//parent process 
			wait(NULL);
			puts("Child process finished.");
		}
		
		should_run = 0;
	}	
	return 0; 
}
