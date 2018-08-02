#include "pwmio.h"
#include "led.h"

static int threshold = 0;

//PWM IO��ʼ��
void PWM_IO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //PWM IO-->PB.7 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOCB.7
 GPIO_SetBits(GPIOB,GPIO_Pin_7); 						 //PB.7 ����� 

}

void SetPWM_Threshold(int val)
{
	threshold = val;
}

void PWM_Handler(void)
{
	static int count = 0;
	count++;
	if (count > 2000)
		count = 0;
	else if(count > threshold)
	{
		PWM_IO = 0;
	}
	else
	{
		PWM_IO = 1;
	}
}
