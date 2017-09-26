#ifndef _MOTORCONTROL_H_
#define _MOTORCONTROL_H_
//Varibles of Sensor
sbit Left_1_led = P2^3;	  
sbit Right_1_led = P2^2;
//Left motor functions
void Left_moto_forward(int level);
void Left_moto_back(int level);
void Left_moto_stop();
//Right motor functions
void Right_moto_forward(int level);
void Right_moto_back(int level);
void Right_moto_stop();
//Vehicle Driving Functions
void Forward_move(int level);
void Back_move(int level); 	  
void Left_turn(int level);
void Right_turn(int level);
void Car_stop();
//PWM Functions
void Left_PWM_out(int level);
void Right_PWM_out(int level);
#endif //_MOTORCONTROL_H_