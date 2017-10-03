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

void do_irq(void){
	int irq_number;
	irq_number = CPU0.ICCIAR & 0x3ff;//��ȡ�жϺţ�֪ͨ�жϿ�ʼִ��

	printf("irq_number = %d\n",irq_number);

	switch(irq_number){
	case 57:
		printf("KEY2\n",irq_number);

		EXT_INT41_PEND = (1 << 1);//����ж�Դ
		ICDICPR.ICDICPR1 = (1 << 25);//����жϻ����ICD
		break;
	case 58:
			mydelay_ms(50);
			if(0 == (GPX1.DAT & (1 << 2)))
				printf("KEY3\n",irq_number);

		EXT_INT41_PEND = (1 << 2);//����ж�Դ
		ICDICPR.ICDICPR1 = (1 << 26);//����жϻ����ICD
		break;
	}
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3ff) | irq_number;//֪ͨICC�жϽ���
}

int main(void)
{
	/*
	 *Config
	 */
	uart_init();
	printf("Hello World!\n");

//-------------------------K2-------------------------//
	GPX1.CON |= (0xf << 4);//����Ϊ�ⲿ�ж�ģʽ
	EXT_INT41_CON = (EXT_INT41_CON & (~(0xf << 4))) | (0x2 << 4);//�����½��ش����ź�

	EXT_INT41_FLTCON0 |= 1 << 15;
	EXT_INT41_FLTCON0 &= ~(1 << 14);//����ѡ�񲻾�ȷ��ʱ�˲�

	EXT_INT41_MASK &= ~(1 << 1);//ʹ���жϴ��ݵ�GIC

	//25 57  -  EINT[9]

	ICDISER.ICDISER1 |= (1 << 25);//ʹ��57���жϼ��
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & (~(0xff << 8)))
			| (0b00000001 << 8);//���ж�57�͵�cpu0
	ICDDCR = 1;//���ü�������ж�
	CPU0.ICCICR = 1;//ʹ��ICC

//-------------------------K3-------------------------//

	GPX1.CON |= (0xf << 8);//����Ϊ�ⲿ�ж�ģʽ
	EXT_INT41_CON = (EXT_INT41_CON & (~(0xf << 8))) | (0x2 << 8);//�����½��ش����ź�

	EXT_INT41_FLTCON0 |= 1 << 23;
	EXT_INT41_FLTCON0 &= ~(1 << 22);//����ѡ�񲻾�ȷ��ʱ�˲�

	EXT_INT41_MASK &= ~(1 << 2);//ʹ���жϴ��ݵ�GIC

	//26 58  -  EINT[10]

	ICDISER.ICDISER1 |= (1 << 26);//ʹ��57���жϼ��
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & (~(0xff << 16)))
			| (0b00000001 << 16);//���ж�57�͵�cpu0
	ICDDCR = 1;//���ü�������ж�
	CPU0.ICCICR = 1;//ʹ��ICC

	while(1)
		;
	return 0;
}
