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
#include <stdlib.h>   /*includes standardlibrary to use function rand()*/
#include "standard.h" /*includes the use of functions rand()*/



volatile int* portE = (volatile int*) 0xbf886110;
int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";


/**************************game code*********************************/
// 0000 1111 = lsb längst upp. De första 4 på raden lyser.
// 1111 0000 = msb längst ner. De sista 4 på raden lyser.
  
#define PIXEL_UNIT 8
#define PAGE 4
int timeoutcount = 0;
int f = 0;
int snakeX = 0;       // snake pos on the x axes. 0 > 512
int snakeY = 16;      // 0 > 32
int direction = 0;    // 
int appleX = 20; 
int appleY = 20;
int gameover = 0; 
int startMeny = 0; 
int r = 1;


/* Lab-specific initialization goes here */
void labinit( void )
{
  // unsigned int sweep = 0x1;
 //PORTE = sweep;
 volatile int* trisE = (volatile int*) 0xbf886100; //initializing pointer to control register for light GPIO pin
 *trisE &= ~0xff; //setting lights as output

  TRISD |= 0xfe0; //Setting prot D as inputs
  TRISF |= 0x2; // btn1 as inputs

  PR2 = 0x7a12; // 80mil/256/10 period register
  T2CON = 0x70; // prescale 1:256 controlregiter
  TMR2 = 0; // clear timer register
  T2CONSET = 0x8000; // start the timer
  return;
}



/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}


/*moves snake*/
void moveSnake(){
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

// clears the displays. 
void clearDisplay(){
  while (f < 512)
  {
    display[f] = display2[f];
    display3[f] = display2[f];
    display4[f] =  display2[f];
    f++; 
  }
  f= 0;
}


/************Light upp the pixel at the right place***************/
void setPixel(int x, int y){
  int i = (y /PIXEL_UNIT); // 19
  display[x + i*128] =  1 << (y - i * PIXEL_UNIT); // display[144] = 15 

  while (*portE > f)
  {
    if (direction == 0)
    {
      x--;
      int i = (y /PIXEL_UNIT);
      display4[x+i*128] |= 1 << (y - i * PIXEL_UNIT); // makes the snake longer in the x axes depending on the points. 
    }
    f++;
  }
  f=0;

  while (f < 512)
  {
    display[f] |= display3[f]; /* display gets the food pixel */
    display[f] |= display4[f]; // main display gets the sanke coordiantes 
    f++; 
  }
  f = 0;  
}

void setPixelFood(int x, int y){
  int i = (y /PIXEL_UNIT); // 19
  display3[x + i*128] =  1 << (y - i * PIXEL_UNIT); // display3 gets the food coordinates  
}

/*Sets the pixel for food*/
void getFood(){
  setPixelFood(appleX, appleY);
}

/*Looks if the food is eaten */
void foodEaten(){
  if(appleX == snakeX && appleY == snakeY){ // looks if snake and food are at the same place
    r = ((r * 7621) + 1) % 32768; // a function that somewhat generates a random number. Not as effectiv as a rand c funciton.
    appleX = r % 127 ;
    appleY = r % 31;
    *portE +=1;  // score
  }
}


// cheaks if the snake cross the bouders and resets the game. 
void boders(){
  if (snakeX < 0 || snakeX >127 || snakeY < 0 ||snakeY > 31)
  {
    gameover = 1; 
  }

  while (gameover){
    clearDisplay();
    display_string(0, "Game Over");
	  display_string(1, "Press BT1");
	  display_string(2, "to Restart");
	  display_string(3, "Welcome!");
	  display_update();

    if (getbtn1()){
      snakeX = 0;       // snake pos on the x axes. 0 > 512
      snakeY = 16;      // 0 > 32
      appleX = 20; 
      appleY = 20;
      gameover = 0;
      *portE =0; 
    }
  }
}
 
void firstStart (){
  display_update();
  display_string(0, "WELCOME TO");
  display_string(1, "our snake game");
  display_string(2, "To start");
  display_string(3, "press BUTTON 1");
  if (getbtn1())
  {
    startMeny = 1; /* code */
  }
  
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

  if (IFS(0) & 0x100){
    IFSCLR(0) = 0x100; //event flag will always be 1. 
    timeoutcount++;
  }

  while (startMeny == 0)
  {
    firstStart();
  }

  if(timeoutcount == 5){
    labinit(); 
    clearDisplay();            // clears the display and food display. 
    getFood();                 //Calls funcktion that gets the apple pixel
    setPixel(snakeX, snakeY);  // display gets the snake pixel and the apple pixel
    moveSnake();               // snake direction disided by the buttons
    foodEaten();               // cheaks if the food is eaten. 
    boders();                  // cheaks if the snake cross the bouders. 
    display_image(0, display); // draws the pixel on the oled display. 
    timeoutcount = 0;
  }
  
}
