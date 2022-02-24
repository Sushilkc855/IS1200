/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int numInCol = 0; // to fix the side effect 

/***********************
void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  printf("%10d ", 2);
  printf("%10d ", 3);
  printf("%10d ", 5);
  printf("%10d ", 7);
  printf("%10d ", 11);
  printf("%10d ", 13);
  printf("\n");
  printf("%10d ", 17);
  printf("%10d ", 19);

  printf("\n");
}
*********************/

/*Prints prime numbers in 6 rows.*/
void print_number(int n){
 // int numInCol; 
  if (numInCol < COLUMNS )
  {
    printf("%10d ", n);
    numInCol++; 
  }
  else
  {
    printf("\n");
    printf("%10d ", n);
    numInCol = 1; 
  }
}

// determines if a number is prime or not
int is_prime(int n){
  int prime = 1; 
  for (int i = 2; i<=n/2; i++)
  {
    if(n%i== 0 && n != 2 && n!=0)
    {
      prime = 0; 
    }
  }
  return prime;
}

// calls two functions that determine if a number is prime or not and prints out the prime number.
void print_primes(int n){
  int i = 2; 
  while (i <= n)
  {
   if (is_prime(i) == 1)
   {
     print_number(i);
   } 
   i++;
  }
}
// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
