#ifndef __PWMIO__H
#define __PWMIO__H	 
#include "sys.h"

#define PWM_IO PBout(7)// PB7

void PWM_IO_Init(void);//��ʼ��
void SetPWM_Threshold(int val);//����PWM��ֵ
void PWM_Handler(void);//PWM������

		 				    
#endif
