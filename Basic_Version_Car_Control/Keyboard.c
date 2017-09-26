#include "stc12c5a.h"
#include "DelayFunctions.h"
#include "Keyboard.h"
#define KeyPort P3
//Reverse Scan Function
unsigned char KeyScan(void){
  unsigned char cord_h,cord_l;       //Variable of line and column 
  KeyPort = 0x0f;              //define column value as 0
  cord_h = KeyPort&0x0f;     
  if(cord_h!=0x0f){
   delay_ms(10);                 //Shaking Inhibition
   if((KeyPort&0x0f)!=0x0f){
    cord_h=KeyPort&0x0f;    //Read the value of column, higher 4 bits set to 0, lower 4 bits remain
    KeyPort=cord_h|0xf0;    //output to P3, set lower bits to 0
    cord_l=KeyPort&0xf0;    //Read the value of line

    while((KeyPort&0xf0)!=0xf0);  //waiting for release and ouput

    return(cord_h+cord_l);  //output the value 
   }
  }
  return(0xff);     
}
//Independent Key P2.7()

//Determine the return Value
/*****Keyborad Design******
   | 1 | 2 | 3 | +10 |
   | 4 | 5 | 6 | -10 |
   | 7 | 8 | 9 |  Aj |
   | T/O | 0 | S | Cf |
   +10: PWM	Duty +10
   -10: PWM Duty -10
   Aj: PWM Duty Ajust
   Cf: PWM Duty Confirm
   T/O: Tracking/Obstable Avoidance Mode
   S: Stop the car
***T:Tracking Mode A:Avoidance Mode*****
*********0-4 Select Speed**************
**************************/
unsigned char KeySelect(void){
  switch(KeyScan()){
  case 0xee : return 1; break;
  case 0xde : return 2; break;
  case 0xbe : return 3; break;
  case 0x7e : return 'I'; break;   //Increase

  case 0xed : return 4; break;
  case 0xdd : return 5; break;
  case 0xbd : return 6; break;
  case 0x7d : return 'D'; break;   //Decrease

  case 0xeb : return 7; break;
  case 0xdb : return 8; break;
  case 0xbb : return 9; break;   
  case 0x7b : return 'A'; break;   //Adjust

  case 0xe7 : return 'T'; break;   //Transfer Mode
  case 0xd7 : return 0; break;
  case 0xb7 : return 'S'; break;   //Stop Car
  case 0x77 : return 'C'; break;   //Confirm

  default : return 0xff; break;	  //No Input
  }
}