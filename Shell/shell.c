// Modify this file for your assignment
#include <unistd.h>
#include <stdio.h>
<<<<<<< HEAD
=======
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#define BUFFSIZE 80

void sigint_handler(int sig){
	printf("\nTerminating through signal handler.\n");
	exit(0);
}

char** parse_function(char* argument){

	//return_input is an array that will hold the tokens, or commands, entered by the user
	char** return_input = malloc(sizeof(char*)*BUFFSIZE);

	//Null check for the malloc
	if(return_input == NULL){
		exit(1);
	}

	//The delimiter is a space and a \n
	char* delim = " \n";

	char* token;
	int i = 0;
	
	//strtok is a built in function. We are creating tokens by separating by the delimiter.
	token = strtok(argument, delim);
	while (token != NULL){
		return_input[i] = token;
		i++;
		token = strtok(NULL, delim);
	}

	return_input[i] == NULL;
	return return_input;
}
>>>>>>> 423bae3f88a896e1863d8cddda6fff58f3575a5c

int main(){
  // Please leave in this line as the first statement in your program.
  alarm(120); // This will terminate your shell after 120 seconds,
              // and is useful in the case that you accidently create a 'fork bomb'
<<<<<<< HEAD
printf("Hello World");  
  
  return 0;
=======
	      
  int pid;

 while (1){

	 //Install the signal handler
	 signal(SIGINT, sigint_handler);

	 //Print the prompt
	 printf("mini-shell> ");

	 char command[BUFFSIZE];

 	 //fgets is a built in command. It will store the user's input from the command line. 
	 char* input = fgets(command, BUFFSIZE, stdin);

	 char** argument = parse_function(input);

	 //Exit the program if the user enters exit
	 if (strcmp(argument[0], "exit") == 0){
		 free(argument);
 		 exit(0);
	 }

	 //Change directories if the user enters cd
	 if (strcmp(argument[0], "cd") == 0){
		 chdir(argument[1]);
		 free(argument);
		 continue;
	 }

	 //Displays a help manual for the available command options if the user enters help
	 if (strcmp(argument[0], "help") == 0){
		 printf("\n");
		 for (int j = 0; j < 15; j++){
			 printf("*");
		 }
		 printf("\nCOMMAND OPTIONS\n");
		 for (int j = 0; j < 15; j++){
			 printf("*");
		 }
		 printf("\n \ncd - Change Directory. Use cd followed by the\n"
			"name of the directory which you would like to\n"
			"enter.\n"
			"Use cd followed by .. to go back into the\n"
			"parent directory.\n \n");
		 printf("help - Open help page for command options.\n \n");
		 printf("guessinggame - Starts a simple number guessing\n"
			"game on the shell.\n \n");
		 printf("exit - terminate all processes and exit the shell.\n \n");
		 free(argument);
		 continue;
	 }

	 //Initiates a simple guessing game if the user enters guessinggame
	 if (strcmp(argument[0], "guessinggame") == 0){
		 int randnum = ( rand()%100 ) + 1; //Generate a random number
		 int guess;

		 printf("\n");
		 for (int k = 0; k < 14; k++){
			 printf("*");
		 }
		 printf("GUESSING GAME");
		 for (int k = 0; k < 14; k++){
			 printf("*");
		 }
		 printf("\n");
		 while (1){			 
			 printf("\nGuess a number from  1 to 100:  "); //Prompt the user for a number
			 scanf("%d", &guess); //Scan the number entered by the user and store in the guess variable
			 if (guess == randnum){
				 printf("You are correct! Great guess!\n");
				 break;
			 }
			 else if (guess < randnum){
				 printf("Your guess was too low. Try again!\n");
			 }
			 else if (guess > randnum){
				 printf("Your guess was too high. Try again!\n");
			 } 
		 }
		 free(argument);
		 continue;
	 }	 

/*	 else {
		 printf("Command not found. Refer to 'help' for command options.\n");
		 continue;
	 }*/

	 //If we reach here, we are not executing a function that has been built into our program
	 
	 //We must fork to execute any Linux built in functions that are passed
	 
	 //Fork, wait and exit are built in functions

	 int fd[2];
	 int pipeExists = 0;

	 //Check if there is a pipe in the command that the user entered. 
	 for (int i = 0; i < sizeof(argument); i++){
		 if (strcmp(argument[i], "|") == 0){			 
		 	 pipeExists = 1;
  	 	}
	 }

	 if (pipeExists = 1){
		pipe(fd);
		int pid1 = fork();
		int pid2 = fork();
		if (pid1 < 0 || pid2 < 0){
			printf("Child processes could not be created!\n");
			break;
		}
		if (pid1 == 0){ // command on the left side of the pipe
			dup2(fd[1], STDOUT_FILENO); // make output go to pipe
			close(fd[0]);
			close(fd[1]);
			execlp(argument[0], argument[0], NULL);
		}
		if (pid2 == 0){ // command on the right side of the pipe{
			dup2(fd[0], STDIN_FILENO); // get input from pipe
			close(fd[0]);
			close(fd[1]);
			execlp(argument[2], argument[2], NULL); // This executes argument[2], since pipe is argument[1]
		}

		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		free(argument);	
	 }

	 pid = fork();

	 if (pid == -1){ // Exit the program if the child process could not be created
		 printf("Child Process could not be created!\n");
		 exit(0);
	 }

	 if (pid == 0){ //We are in our child process
		 //execvp is a built in function
	        execvp(argument[0], argument);
		exit(0);
	 }
	 else {
		 wait(NULL);
	 }
	 
	 free(argument);
}

	return 0;
>>>>>>> 423bae3f88a896e1863d8cddda6fff58f3575a5c
}
