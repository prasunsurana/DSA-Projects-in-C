// gcc -Wall factorial.c -o factorial
// ./factorial

#include <stdio.h>

unsigned long long int factorial(int n){
  // TODO: Implement iterative solution here

	if (n < 0){
		return -9999;
	}

	if (n == 0){
		return 1;
	}

	unsigned long long int factorial = 1;

	while (n > 0){
		factorial = factorial*n;
		n--;
	}

  return factorial;
};

unsigned long long int factorial_rec(int n){
  // TODO: Implement recursive solution here

	if (n < 0){
		return -9999;
	}

	if (n == 0){
		return 1;
	}

	while (n > 0){
		return n*factorial_rec(n-1);
	}

  return 0;
}

int main(){

  // Both of these should print the same result!
  printf("factorial(10) = %llu\n",factorial(21));
  printf("factorial_rec(10) = %llu\n",factorial_rec(21));


  return 0;
}
