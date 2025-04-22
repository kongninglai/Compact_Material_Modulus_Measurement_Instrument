#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
void PWM_Tim3Init(unsigned int pres,unsigned int period);
void PWM_SetCompare1(uint16_t Compare);
void PWM_Start(void);
void PWM_Stop(void);
void PWM_Steps(unsigned int steps);
#endif
