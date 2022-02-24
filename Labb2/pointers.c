/*https://stackoverflow.com/questions/33829566/for-loop-with-pointer-in-c/34289302
https://www.programiz.com/c-programming/c-pointers-arrays
https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Pointers.html
https://www.codegrepper.com/code-examples/c/how+to+print+value+of+pointer+in+c
*/
#include <stdio.h>

char* text1 = "This is a string."; //text1[0] = t text1[1] = h. text1 = adress till t. text1 +1 adredss till h. 
char* text2 = "Yet another thing.";
// Array size 20 since asm specifies 80 bytes of storage and ints have 4 byte size
int list1[20]; 
int list2[20]; 
int count = 0; 


void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

void copycodes(char *first, int *second, int *charCount){
  while (*(first) != 0)
  {
    *second = *first; //*(first + i) is is equivalent to first[i] 
     // Order of operation for dereferencing and incrementing are the same,
    (*charCount)++;
    first++;
    second++; 
  }
}

void work(){
  copycodes(text1, list1, &count); 

   copycodes(text2, list2, &count); 
}



int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
