#include "stc12c5a.h"
#include <intrins.h>
#include "DelayFunctions.h"
#include "DistanceCalculate.h"
#include "MotorControl.h"
#include "Keyboard.h"
//Mode Identification
sbit S_led = P2^7;
sbit A_led = P2^6; //Temporary Using for Indicate
//For Distance Detection
unsigned int O_Distance;

void main(void){
  //Keyboard Status Detection
  unsigned char KeyFlag = 0xff;
  bit MFlag = 0;         //Mode Flag
  unsigned char TempFlag;	   //Temporary Flag to Store Selecting Key Input
  int PWMlevel[3];   //To store the Value of PWM Level
  int PWMvalue = 256;	   //The Real Value of PWM. Cannot use unsigned int because it can be decreased under 0
  unsigned int waiting = 0;  //Obstacle Signal Waiting Time
  //About PWM Control
  CCON = 0;	   
  CL = 0;	  
  CH = 0;	  
  CMOD = 0x00;	   //Fpwm = SYSclk/(12*256)*/
  Car_stop();       //Reset
  while(1){
    //Determing the Status
	KeyFlag = KeySelect();
	if(KeyFlag!=0xff){
	   if(KeyFlag == 'A'){
	     unsigned int i = 0;
		 while(1){
		   A_led = 0;	   //Temporary Indicate
		   TempFlag = KeySelect();
		   if(i<3){
		 	  switch(TempFlag){
			  	  case 0 : PWMlevel[i] = 0; i++; break;
				  case 1 : PWMlevel[i] = 1; i++; break;
			  	  case 2 : PWMlevel[i] = 2; i++; break;
				  case 3 : PWMlevel[i] = 3; i++; break;
				  case 4 : PWMlevel[i] = 4; i++; break;
				  case 5 : PWMlevel[i] = 5; i++; break;
				  case 6 : PWMlevel[i] = 6; i++; break;
				  case 7 : PWMlevel[i] = 7; i++; break;
				  case 8 : PWMlevel[i] = 8; i++; break;
				  case 9 : PWMlevel[i] = 9; i++; break;
				  default : break;
			    }
			  }
		   if(TempFlag == 'C'){
		 	   PWMvalue =  100*PWMlevel[0] + 10*PWMlevel[1]	+ PWMlevel[2];
			   i = 0;
			   A_led = 1;	   //Temporary Indicate
			   break;
		     }		  
		 }
	   }	  //End of PWM Adjust Input
	   if(KeyFlag == 'I'){
	   	  PWMvalue = PWMvalue + 10;
		  PWMlevel[0] = PWMvalue/100;
		  PWMlevel[1] = (PWMvalue%100)/10;
		  PWMlevel[2] =  PWMvalue%10;
	   } //End of Increase
	   if(KeyFlag == 'D'){
	   	  PWMvalue = PWMvalue - 10;
		  PWMlevel[0] = PWMvalue/100;
		  PWMlevel[1] = (PWMvalue%100)/10;
		  PWMlevel[2] =  PWMvalue%10;
	   } //End of Decrease
	   //PWM No More Than 256
	   if(PWMvalue > 256){
		  	 PWMvalue = 256;
			 PWMlevel[0] = 2;
			 PWMlevel[1] = 5;
			 PWMlevel[2] = 6;
		}
	   //PWM No Less Than 0
	   if(PWMvalue <= 0){
		  	 PWMvalue = 0;
			 PWMlevel[0] = 0;
			 PWMlevel[1] = 0;
			 PWMlevel[2] = 0;
		  }
	   if(KeyFlag == 'T'){
	   	  MFlag = !MFlag;
	   } //End of Mode Transfer
	   if(KeyFlag == 'S'){
	   	  PWMvalue = 0;
		  PWMlevel[0] = 0;
		  PWMlevel[1] = 0;
		  PWMlevel[2] =  0;
		  Car_stop();
	   }//End of Car Stop
	}//End of Matrix Keyborad Determination
	//About Car Action
	if(MFlag == 0){
	   S_led = 0;
	   if(Left_1_led==0 && Right_1_led==0){
         Forward_move(PWMvalue);				 
	   }
       else{			  
	      if(Left_1_led==1 && Right_1_led==0){	 //Black line on the left side
	        Left_turn(PWMvalue);						 //Trun left
	      }
	      if(Left_1_led==0 && Right_1_led==1){	 //Black line on the left side 
	        Right_turn(PWMvalue);		   //Turn Right
	      }
	    }
	}
	else{
	   S_led = 1;
	   M_rx = 1;
	   Emission();
	   while(1){
	     if(M_rx==1){
           O_Distance = Distance_calculate();
		   break;		 
		 }
	    waiting++;
	     if(waiting>2000){
	       OFflag = 1;
	       waiting = 0;
	  	   break;
	     }	
       }
	   if(O_Distance>6000||OFflag==1){
	     Forward_move(PWMvalue);
	   }
	   else if(O_Distance>1500){
	   	 Forward_move(PWMvalue);
	   }
	   else if(O_Distance>500){
	   	 Forward_move(PWMvalue/2);
	   }
	   else if(O_Distance>200){
	   	 Right_turn(PWMvalue);
	   }
	   else{
	   	 Back_move(PWMvalue);
	   }
	   OFflag = 0;
	}
  }//End of Main Loop
}//End of Main Function