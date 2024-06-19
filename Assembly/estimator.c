// Implement your cycle count tool here.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	

	//Declare an array to store the count for each assembly instruction
	int count[] = {};

	//Initialize all values in a 'count' array to 0
	for (int i = 0; i < 9; i++){
		count[i] = 0;
	}
	
	char sentence[50];

	//Initialize variables that count total instructions and total cycles
	int totalInstructions = 0;
	int totalCycles = 0;

	//Reading in the file
	FILE* filePointer;
	filePointer = fopen(argv[1],"r");

	if (filePointer == NULL){		
		printf("File cannot be opened\n.");
		return -1;
	}	

	//Iterating over each line in the file to find our instruction words
	while(fgets(sentence, 50, filePointer)){
		
		if (strcasestr(sentence, "add")){
			totalInstructions = totalInstructions + 1;
			totalCycles = totalCycles + 1;
			count[0] = count[0] + 1;
		}
		if (strcasestr(sentence, "sub")){
                        totalInstructions = totalInstructions + 1;
                        totalCycles = totalCycles + 1;
			count[1] = count[1] + 1;					
		}	
		if (strcasestr(sentence, "mul")){
			totalInstructions = totalInstructions + 1;
			totalCycles = totalCycles + 3;
			count[2] = count[2] + 1;
		}
		if (strcasestr(sentence, "div")){
			totalInstructions = totalInstructions + 1;
			totalCycles = totalCycles + 24;
			count[3] = count[3] + 1;
		}	 
		if (strcasestr(sentence, "mov")){
			totalInstructions = totalInstructions + 1;
			totalCycles = totalCycles + 1;
			count[4] = count[4] + 1;
		}
		if (strcasestr(sentence, "lea")){
			totalInstructions = totalInstructions + 1;
			totalCycles = totalCycles + 3;
			count[5] = count[5] + 1;
		}
		if (strcasestr(sentence, "push")){
			totalInstructions = totalInstructions + 1;
			totalCycles = totalCycles + 1;
			count[6] = count[6] + 1;
		}
		if (strcasestr(sentence, "pop")){
			totalInstructions = totalInstructions + 1;
			totalCycles = totalCycles + 1;
			count[7] = count[7] + 1;
		}
		if (strcasestr(sentence, "ret")){
			totalInstructions = totalInstructions + 1;
			totalCycles = totalCycles + 1;
			count[8] = count[8] +1 ;
		}

	}

	//Create an array to store all assembly instructions
	char *words[] = {
			"add\0",
			"sub\0",
			"mul\0",
			"div\0",
			"mov\0",
			"lea\0",
			"push\0",
			"pop\0",
			"ret\0"
	};	

	for (int k = 0; k < 9; k++){
		printf("%s appeared in the file %d times!\n", words[k], count[k]);
	}

	printf("Total Instructions = %d\n", totalInstructions);
	printf("Total Cycles = %d\n", totalCycles);		

	fclose(filePointer);
	return 0;
}
