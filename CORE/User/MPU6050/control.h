#ifndef  _CONTROL_H
#define  _CONTROL_H

#include "sys.h" 

int Vertical(float Med,float Angle,float gyro_Y);
int Velocity(int encoder_left,int encoder_right);
int Turn(int gyro_Z);
void EXTI4_IRQHandler(void);

#endif


