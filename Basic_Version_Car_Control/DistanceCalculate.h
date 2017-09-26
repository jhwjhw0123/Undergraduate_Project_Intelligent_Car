#ifndef _DISTANCECALCULATE_H_
#define _DISTANCECALCULATE_H_
//Distance avoidance module
sbit M_tx = P2^1;
sbit M_rx = P2^0;
//Detection time
extern unsigned char OFflag;
//Detection signal emission
void Emission();
//Distance calculation 
unsigned int Distance_calculate();
#endif //_DISTANCECALCULATE_H_