#include <stdio.h>
#include <stdlib.h>

int main(){
	int randnum;
	int guess;
	int array[5] = {0,0,0,0,0};	
	
	for (int round = 0; round < 5; round++){
		printf("----------\n");
		printf("ROUND %d\n", round+1);
		printf("----------\n");		
		for (int j = 0; j < 1; j++){
			randnum = ( rand()%10 ) + 1;
			while (1){
				printf("Guess a number from 1 to 10:  ");
				scanf("%d", &guess);
				if ((guess > 0) && (guess < 11)){
					if (guess == randnum){
						printf("You are correct!\n");
						array[round]++;
						break;
						}	
					else if (guess > randnum){
						printf("Your guess is too high!\n");
						array[round]++;
						}
					else {
						printf("Your guess is too low!\n");
						array[round]++;
						}
				}
				else {
					printf("Your number is out of range!\n");
					}
			}
		}
	}
	printf("----------\n");
	printf("RESULTS\n");
	printf("----------\n");
	for (int k = 0; k < 5; k++){
		printf("The number of guesses in Round %d was %d.\n", k+1, array[k]);
			}
}		
