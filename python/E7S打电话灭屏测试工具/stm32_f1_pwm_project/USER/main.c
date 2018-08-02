#include "string.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "pwmio.h"

int main(void)
{
	u16 recv_len=0;
	u16 led0pwmval=0;
	u8 dir=1;	
	u8 send_buf[1024];
	delay_init();           //��ʱ������ʼ��	  
	NVIC_Configuration();   //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);      //���ڳ�ʼ��Ϊ115200
	LED_Init();             //LED�˿ڳ�ʼ��
	PWM_IO_Init();          //PWM IO�˿ڳ�ʼ��
	TIM3_Int_Init(10,71); //1Mhz�ļ���Ƶ�ʣ�������10Ϊ0.1ms
	//TIM3_Int_Init(1000,71); //1Mhz�ļ���Ƶ�ʣ�������1Ϊ1s
	printf("Ready\r\n");
	
	//SetPWM_Threshold(500);

//	SetPWM_Threshold(50);//0.5ms,0��
//	SetPWM_Threshold(100);//1.0ms,45��
//	SetPWM_Threshold(150);//1.5ms,90��

	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			recv_len = USART_RX_STA & (0x3fff);
			strncpy((char *)send_buf,(char *)USART_RX_BUF,recv_len);
			send_buf[recv_len] = '\0';
			printf(send_buf);printf("\r\n");
			if(!strncmp((char *)USART_RX_BUF,"LED_ON",recv_len))
				LED0 = 0;
			if(!strncmp((char *)USART_RX_BUF,"LED_OFF",recv_len))
				LED0 = 1;
			if(!strncmp((char *)USART_RX_BUF,"PWM_0",recv_len)){
				SetPWM_Threshold(5);//0.5ms,0��
			}
			if(!strncmp((char *)USART_RX_BUF,"PWM_45",recv_len)){
				SetPWM_Threshold(10);//1.0ms,45��
			}
			if(!strncmp((char *)USART_RX_BUF,"PWM_90",recv_len)){
				SetPWM_Threshold(15);//1.5ms,90��
			}
			USART_RX_STA = 0;
		}
	}
}

