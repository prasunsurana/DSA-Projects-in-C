// Task: Implement the divide-and-conquer algorithm 
// for calculating mixed-up-ness score

// =================== Libraries ==================
#include <stdio.h> // Include file for standard input/output

// =============== Helper Functions ===============
// TODO: Implement your helper functions here


//Below is the merge function.
//Name: merge
//Inputs:
//	(1) arr - This is a pointer to an integer address. 
//	This is the start of some contiguous block of memory that we will sort.
//	(2) temp - This is a pointer to an integer address.
//	This will store the merged array.
//	(3) l - The leftmost index of the array.
//	(4) m - The midpoint index of the array.
//	(5) r - The rightmost index of the array. 
int merge(int arr[], int temp[], int l, int m, int r){

	//Null check on function parameters
	if (arr == NULL || temp == NULL){
		return 1;
	}

	int i = l;
	int j = m;
	int k = l;
	int score = 0;

	while (i <= m-1 && j <= r){
		if (arr[i] <= arr[j]){
			temp[k] = arr[i];
			i++;
			k++;
		}
		else {
			temp[k] = arr[j];
			j++;
			k++;
			score = score + (m-i); // This is done because when two arrays are merged, they are already sorted. So if
				 	    // the arr[j] (element in the right array) is smaller than arr[i] (element in the 
				 	    // left array), that means arr[j] is also smaller than the elements in the left array
				 	    // that come after arr[i]. To capture the unsorted pairs here, we increment the score
				 	    // by adding mid-i, since those are the remaining number of elements in the left
				 	    // array that are greater than arr[j], and hence unsorted. 
		}
	}

        //It may be the case that all the elements of one of the sub-arrays may be added to temp, but
        //there are still remaining elements in the other array. Since the sub-arrays are already
        //sorted, we can just populate temp with with the remaining elements in the sub-arrays.
        while (i <= m-1){
		temp[k] = arr[i];
		i++;
		k++;
	}

	while (j <= r){
		temp[k] = arr[j];
		j++;
		k++;
	}

	//Copy temp's elements into the original array
	for (k = l; k <= r; k++){
		arr[k] = temp[k];
	}

	return score;

}     


//Name: mergeSort
//Inputs: 
//	(1) arr - This is a pointer to an integer address.
//	This is the start of some contiguous block of memory that we will sort.
//	(2) temp - This is a pointer to an integer address.
//	This will store the merged array.
//	(3) l - The leftmost index of the array.
//	(4) r - The rightmost index of the array. 
int mergeSort(int arr[], int temp[], int l, int r){

	//Null check on function parameters
	if (arr == NULL || temp == NULL){
		return 1;
	}

	// Array of size 1 is trivially sorted
	if (l == r){
		return 0;
	}

	//Exit function if l is greater than r
	if (l > r){
		return 1;
	}

	int score = 0;

	if (r > l){
		int m = (l + r)/2;
		score = score + mergeSort(arr, temp, l, m);
		score = score + mergeSort(arr, temp, m+1, r);
		score = score + merge(arr, temp, l, m+1, r);
	}

	return score;

}


// Provided below is a mixed-up-ness score.
// Name: mixedupness
// Input(s):
//    (1) 'array' is a pointer to an integer address. 
//         This is the start of some 'contiguous block of memory' that we will sort.
//    (2) 'size' tells us how big the array of data is we are sorting.
// Output: The mixedupness score of the original array
int mixedupness(int* array, unsigned int size){
  // TODO: Implement me!!

	//Null check on function parameters
	if (array == NULL || size == 0){
		return 1;
	}

	int temp[size];
	return mergeSort(array, temp, 0, size - 1);

}


// Input: A pointer to an array (i.e. the array itself points to the first index)
//        The size of the array (Because we do not know how big the array is automatically)
void printIntArray(int* array, unsigned int size){
  unsigned int i; // Note: 'unsigned int' is a datatype for storing positive integers.
  for(i = 0; i < size; i=i+1){
    printf("%d ",array[i]);
  }
  printf("\n");
}

int main(int argc, char** argv){
  // Some test data sets.
  int dataset1[] = {0,1,2,3,4,5,6,7,8,9,10};
  int dataset2[] = {100,87,65,10,54,42,27,37};
  int dataset3[] = {0,3,2,1,4,7,6,5,8,9,10};
  int dataset4[] = {10,9,8,7,6,5,4,3,2,1,0};
  int dataset5[] = {100,201,52,3223,24,55,623,75,8523,-9,150};
  int dataset6[] = {-1,1,2,-3,4,5,-6,7,8,-9,10};

  // Print out an array
  printf("dataset 1: ");
  printIntArray(dataset1, 11);
  printf("dataset 2: ");
  printIntArray(dataset2, 8);
  printf("dataset 3: ");
  printIntArray(dataset3, 11);
  printf("dataset 4: ");
  printIntArray(dataset4, 11);
  printf("dataset 5: ");
  printIntArray(dataset5, 11);
  printf("dataset 6: ");
  printIntArray(dataset6, 11);
  printf("\n");
  
  // TODO: Change these so that they print 
  // both the expected score and the calculated score
  printf("dataset 1 expected = %d, actual = %d\n", 0, mixedupness(dataset1, 11));
  printf("dataset 2 expected = %d, actual = %d\n", 23, mixedupness(dataset2, 8));
  printf("dataset 3 expected = %d, actual = %d\n", 6, mixedupness(dataset3, 11));
  printf("dataset 4 expected = %d, actual = %d\n", 55, mixedupness(dataset4, 11));
  printf("dataset 5 expected = %d, actual = %d\n", 27, mixedupness(dataset5, 11));
  printf("dataset 6 expected = %d, actual = %d\n", 18, mixedupness(dataset6, 11));
  
  return 0;
}
