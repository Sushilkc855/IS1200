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
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  int button = getbtns();
  int switches = getsw();

  if(button){
    if(button == 1){
       mytime = mytime & 0xff0f;  
       mytime = (switches<<4) |mytime ;
    }
    if(button == 2){
      mytime = mytime & 0xf0ff;  
       mytime = (switches<<8) |mytime ;
    }
    if(button == 4 ){
      mytime = mytime & 0x0fff;  
       mytime = (switches<<12) |mytime ;
    }
  }

  delay( 1000 );
  time2string( textstring, mytime );
  *portE +=1; 
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
}
