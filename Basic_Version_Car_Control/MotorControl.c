/************************************
******Motor Control Source File******
*****PWM Level: 0-256(0:Stop 256:Full Speed)******
*************************************/
#include "stc12c5a.h"
#include "DelayFunctions.h"
#include "MotorControl.h"
//H bridge control the machine
//Left
sbit IN1 = P1^1;
sbit IN2 = P1^2;
sbit EN1 = P1^3;
//Right
sbit IN3 = P1^6;
sbit IN4 = P1^7;
sbit EN2 = P1^4;


void Left_moto_forward(int level){
  Left_PWM_out(level);
  IN1 =	0;
  IN2 = 1;
}

void Right_moto_forward(int level){
  Right_PWM_out(level);
  IN4 = 0;
  IN3 = 1;
}

void Left_moto_stop(){
  Left_PWM_out(0);
  IN1 = 0;
  IN2 = 0;
}

void Right_moto_stop(){
  Right_PWM_out(0);
  IN3 = 0;
  IN4 = 0;
}

void Left_moto_back(int level){
  Left_PWM_out(level);
  IN1 = 1;
  IN2 = 0;
}

void Right_moto_back(int level){
  Right_PWM_out(level);
  IN4 = 1;
  IN3 = 0;
}

void Forward_move(int level){
  Left_moto_forward(level);
  Right_moto_forward(level); 
}

void Back_move(int level){
  Left_moto_back(level);
  Right_moto_back(level);
} 

void Car_stop(){
  Left_moto_stop();
  Right_moto_stop();
}

void Left_turn(int level){
  Left_moto_stop();
  Right_moto_forward(level);
}

void Right_turn(int level){
  Right_moto_stop();
  Left_moto_forward(level);
}

void Left_PWM_out(int level){
   PCA_PWM0 = 0x00;
   if(level == 0){
   	  CCAP0L = 0xff; 	  //Two datas must be the same
      CCAP0H = 0Xff;
	  PCA_PWM0 = 0x03;
     }
   else if(level == 256){
   	  CCAP0L = 0x00;
	  CCAP0H = 0x00;
	  PCA_PWM0 = 0x00;
     }
   else{
   	  	CCAP0L = 256 - level;
		CCAP0H = 256 - level;
     }
   CCAPM0 = 0x42;  //enable PWM, left(P1.3)
   CR = 1;
}

void Right_PWM_out(int level){
  PCA_PWM1 = 0x00;	  //avoid consistent low
   if(level == 0){
   	  CCAP1L = 0xff; 	  //Two datas must be the same
      CCAP1H = 0Xff;
	  PCA_PWM1 = 0x03;
     }
   else if(level == 256){
   	  CCAP1L = 0x00;
	  CCAP1H = 0x00;
	  PCA_PWM1 = 0x00;
     }
   else{
   	  	CCAP1L = 256 - level;
		CCAP1H = 256 - level;
     }
   CCAPM1 = 0x42;  //enable PWM, left(P1.3)
   CR = 1;
}