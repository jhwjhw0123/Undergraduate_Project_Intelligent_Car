#include "stc12c5a.h"
#include <intrins.h>
#include "DelayFunctions.h"
#include "DistanceCalculate.h"
float c_time = 0;
float d_time = 0;
unsigned char OFflag = 0;
//Detection signal emission
void Emission(){
   M_tx = 1;
   delay_us(30);
   M_tx = 0;
}
//Distance Calculate Function
unsigned int Distance_calculate(){
    unsigned int distance;
	TMOD = 0x01;              //16-bit Timer
	AUXR = 0x00;
    EA = 1;					  //Enable interrut    
    ET0 = 1;                  //Enable T0 interrupt
	TH0 = 0;
    TL0 = 0;      
  	TR0 = 1;			    //Start Timer
	while(M_rx);	    //Warting for M_rx signal
    c_time = TH0*256 + TL0;	   //measure:us, each d_time need 1.085us (12T mode)
    d_time = c_time/1.085;	   //Real time of ultrasonic
	distance = (int)(10*d_time*0.344/2);  //measure:mm(*10), 0344mm/us is the speed of ultrasonic
	TH0 = 0;				  //Reset Timer
	TL0 = 0;
	TR0 = 0;				//Disable Timer
	return distance;
}

void T0inter() interrupt 1{
   TH0 = 0;
   TL0 = 0;
   M_rx = 0;
   OFflag = 1;
}