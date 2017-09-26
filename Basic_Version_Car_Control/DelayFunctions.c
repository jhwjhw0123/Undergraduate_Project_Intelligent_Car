#include "DelayFunctions.h"
//ms Delay Function
void delay_ms(unsigned int z){
   unsigned int x,y;
   for(x=z; x>0; x--){
	  for(y=848; y>0; y--);	  
	   }
}	
//us Delay Function
void delay_us(unsigned int t){
   unsigned int m = (int)((t*11.0592 - 24)/13);
   unsigned int i;
   for(i=m;i>0;i--);
}