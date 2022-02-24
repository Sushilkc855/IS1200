#include <stdio.h>

char* text1 = "This is a string."; // text1[16]
char* text2 = "Yet another thing.";

char list1[80]; 
char list1[80]; 
int *count; 
/*
void work(){
  char *first = text1;
  char *second = list1; 
  int *count = count; 
  copycodes(first, second, count); 
}
*/
// void copycodes(char *first, char *second, int *count){}

int main(void){
    char *first = text1; //first gets the adress pointed by text1 
  char *second = list1; 
  int *count = count; 

  /*Print the value pointed to by text1*/
  printf("The value of text is: %p\n", *text1);
  /*Print the address pointed to by text1*/
 printf("The adress of text is: %p\n", text1);
 /*Print the address of text1 itself*/
    printf("The direction of text1 is: %p\n", &text1);

/*Print the address pointed to by first*/
     printf("The value of text is: %p\n", first);
      printf("The value of text is: %p\n", *first);

/*
    printf("The value of p is: %p\n", p);
    printf("The direction of p is: %p\n", &p);

    printf("The direction of s[0] is: %p\n", &s[0]);
    printf("The direction of s[1] is: %p\n", &s[1]);
    printf("The direction of s[2] is: %p\n", &s[2]);
*************/
 // copycodes(first, second, count); 
 int n;              /* an int variable */
    int *p;             /* a pointer to an int */
    int *q;             /* another pointer to an int */
   
    p = &n;             /* p now points to n */
    q = p;              /* q now points to n as well */
}
