#include "exynos_4412.h"

void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

int main(void)
{
	int value;

	uart_init();
	printf("ADC test:\n");

	GPK2.CONPDN &= (~(0xff << 8));//GPIOK2_2����Ϊinput

	ADCMUX = 0b0011;//ͨ��3 AIN3

	ADCCON |= (1<<16);//ת��������Ϊ16λ
	ADCCON |= (1<<14);//ʹ��ADCʱ���źŷ�Ƶ��
	ADCCON |= (0xff<<6);//��Ƶϵ��Ϊ256
	ADCCON &= (~(1<<2));//Normal operation mode ��������ģʽ
	ADCCON |= (1<<1);//����Ϊ�ɶ�

	while(1)
	{
		ADCCON |= (1<<0);//��ʼADCת��
		while( !(ADCCON&(~(1<<15))) );
		value =ADCDAT &0xfff;
		printf("ADC value = %d\tV:%d mv\n",value,value*1800/4096);
		mydelay_ms(500);
	}
	return 0;
}
