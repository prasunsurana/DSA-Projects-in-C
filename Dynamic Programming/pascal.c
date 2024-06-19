// Compile with: gcc -Wall pascal.c -o pascal
// Run with: ./pascal 42
#include <stdio.h>
#include <stdlib.h>

#define LARGEST_TRIANGLE 100

// calculate and return the i-th row of Pascal's Triangle
// rowIndex = the index of the row that should be calculated
// returnSize = the size of the row that was calculated
// returns a pointer to an array of size `returnSize`,
//    assume that the caller calls free on the returned array
//
// coincidentally, this problem is the same as one of the problems
// on LeetCode: https://leetcode.com/problems/pascals-triangle-ii/
int* getRow(int rowIndex, int* returnSize){
   // TODO: Implement me!!

	//Create an array to hold all elements in a given row in Pascal's Triangle
	int* pascal = (int*)malloc(sizeof(int)*LARGEST_TRIANGLE);

	//Check if malloc was unable to allocate memory
	if (pascal == NULL){
		return NULL;
	}

	//Initialize the array with 0s
	for (int i = 0; i < LARGEST_TRIANGLE; i++){
		pascal[i] = 0;
	}

	//Create the first row of Pascals triangle
	pascal[0] = 1;

	for (int i = 1; i < rowIndex + 1; i++){
		for (int j = i; j > 0; j--){
			pascal[j] = pascal[j] + pascal[j-1];
		}
	}

   return pascal;
}


int main(int argc, char* argv[]) {
   // Make sure that there is one argument
   if (argc != 2) {
      printf("One argument expected: ./pascal 42\n");
      return 1;
   }

   // Convert the argument of the program into an integer
   // and make sure that it is between 0 and LARGEST_TRIANGLE - 1
   const int row = atoi(argv[1]);
   if (row < 0 || row > LARGEST_TRIANGLE - 1) {
      printf("row must between 0 and %d (inclusive)\n", LARGEST_TRIANGLE - 1);
      return 1;
   }

   int size = 30;
   int* row_values = getRow(row, &size);

   printf("Row %d of Pascal's Triangle\n", row);
   for(int i = 0 ; i < size ; i++) {
      printf("%d ", row_values[i]);
   }
   printf("\n");

   // free the memory that was returned from function
   free(row_values);
   return 0;
}
