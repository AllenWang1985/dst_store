#include "interrupt.h"

void (*fun_p[160])();

void do_irq(void) {
	int irq_number;
	irq_number = CPU0.ICCIAR & 0x3ff; //��ȡ�жϺţ�֪ͨ �жϿ�ʼִ��
	printf("irq_number = %d\n", irq_number);

	if (irq_number <= 159)
		(*fun_p[irq_number])();

	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3ff) | irq_number; //֪ͨicc�жϽ���
}
