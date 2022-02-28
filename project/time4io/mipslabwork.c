/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
volatile int* portE = (volatile int*) 0xbf886110;
int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";
/**************************game code*********************************/
// 0000 1111 = lsb längst upp. De första 4 på raden lyser.
// 1111 0000 = msb längst ner. De sista 4 på raden lyser.
  
#define PIXEL_UNIT 8
#define PAGE 4
  int f = 0;
  int snakeX = 0;       // snake pos on the x axes.
  int snakeY = 16; 
  int direction = 0;
  int temp = 0; 
  int array = 0;  
/*moves snake*/
void moveSnakeX(){
  if (direction == 0){ //höger
    snakeX++;
  }
  if (direction == 1) //upp
  {
    snakeY++; 
  }
  if (direction == 2) //ner
  {
    snakeY--; 
    /*
    temp = 0xff; 
    temp = ~display[snakeY] & temp;
    display[snakeY] = (display[snakeY] << 1) | temp;*/
  }
  if (direction == 3) //vänster
  {
    snakeX--; 
  }
}

void clearDisplay(){
    while (f < 512)
    {
     display[f] = display2[f]; /* code */
     f++; 
    }
f= 0;
}


/************Light upp the pixel at the right place***************/
void setPixel(int x, int y){
  int i = (y /PIXEL_UNIT); // 19
  display[x + i*128] =  1 << (y - i * PIXEL_UNIT); // display[144] = 152   
}



/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
// unsigned int sweep = 0x1;
 //PORTE = sweep;
 volatile int* trisE = (volatile int*) 0xbf886100; //initializing pointer to control register for light GPIO pin
 *trisE &= ~0xff; //setting lights as output

  TRISD |= 0xfe0; //Setting prot D as inputs
  TRISF |= 0x2;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  int button = getbtns(); // button status 
  int switches = getsw(); // switch status
  int button1 = getbtn1();

  if(button || button1){
    if(button1 == 1){
      direction = 0; // höger
    }
    if(button == 1){
      direction = 1; // upp
    }
    if(button == 2){
      direction = 2;//ner
    }
    if(button == 4){
      direction = 3; // vänster
    }
  }
 labinit();
  delay(400); 
  //time2string( textstring, mytime );
  //*portE +=1; 
  //display_string( 3, textstring );
   clearDisplay();
   setPixel(snakeX, snakeY); 
    moveSnakeX();
   
 // display_update();
  //display_image(0, display );
  //tick( &mytime );
  display_image(0, display);
}
