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
int prime = 1234567;

volatile int* portE = (volatile int*) 0xbf886110;
int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

 int timeoutcount = 0;


/* Interrupt Service Routine */
void user_isr( void ) {

 if (IFS(0) & 0x100){
  IFSCLR(0) = 0x100; //event flag will always be 1. 
   timeoutcount++;
}

 if(timeoutcount == 10){
tick( &mytime );
 time2string( textstring, mytime );
 display_string( 3, textstring );
 display_update();
 timeoutcount = 0;
 }

/*sw2*/
 if (IFS(0) & 0x800){
   mytime += 3; 
   IFSCLR(0) = 0x800;
 }
}


/* Lab-specific initialization goes here */
void labinit( void )
{
// unsigned int sweep = 0x1;
 //PORTE = sweep;
 volatile int* trisE = (volatile int*) 0xbf886100; //initializing pointer to control register for light GPIO pin
 *trisE &= ~0xff; //setting lights as output

  TRISD |= 0xfe0; //Setting prot D as inputs
	
  T2CON = 0x0070; // prescale 1:256 controlregiter
  TMR2 = 0; // clear timer register
  PR2 = 0x7a12; // 80mil/256/10 period register
  T2CONSET = 0x8000; // start the timer
  
  
  // Inrerrupt Enable control on. Bit 8 is for T2IF
  IECSET(0) = 0x100; 
  // Inrerrupt Priotet control 
  IPCSET(2) = 0x1f;
  
  /** Surprise assignment ****/
  // Inrerrupt Enable control on. Bit 11 is for SW2
  IECSET(0) = 0x800;
  // Inrerrupt Priotet control 
  IPCSET(2) = 0x1f000000; 


  // Enable interrupts globally
    enable_interrupt();
  return;
}

void labwork( void ) {
  prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
 display_update();
}

/* This function is called repetitively from the main program */
/*
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

if (IFS(0) & 0x100){
  IFSCLR(0) = 0x100; //event flag will always be 1. 
   timeoutcount++;
}

***********************
int time; 
time = IFS(0) & 0x100; // interupt flag
while (timeoutcount < 10)
{
  while (  time == 0) 
  {
    time = IFS(0) & 0x100;
  }
   IFSCLR(0) = 0x100;
   time = IFS(0) & 0x100;
   timeoutcount++;
}
************************
   // delay( 1000 );
   if(timeoutcount == 10){
  time2string( textstring, mytime );
  *portE +=1; 
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
 timeoutcount = 0;
   }
}
*/