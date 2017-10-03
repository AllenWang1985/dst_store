#include "key.h"

void key2_int() {

	timer4_start(50, 2);

	EXT_INT41_PEND = (1 << 1); // ����ж�Դ
	ICDICPR.ICDICPR1 = (1 << 25); //����жϻ����ICD
}

void key3_int() {

	timer4_start(50, 3);

	EXT_INT41_PEND = (1 << 2); // ����ж�Դ
	ICDICPR.ICDICPR1 = (1 << 26); //����жϻ����ICD
}

void key_init() {

	timer4_open();

	// --------------------------key2-------------------------
	GPX1.CON |= (0xf << 4); //����Ϊ�ⲿ�ж�ģʽ
	EXT_INT41_CON = (EXT_INT41_CON & (~(0XF << 4))) | (0X2 << 4); //���� �½����źŴ����ж�

	EXT_INT41_FLTCON0 |= 1 << 15;
	EXT_INT41_FLTCON0 &= ~(1 << 14); //������ѡ�񲻾�׼��ʱ�˲�

	EXT_INT41_MASK &= ~(1 << 1); //ʹ���жϴ��ݵ� GIC

	//25  57  �C  EINT[9]
	fun_p[57] = key2_int;

	ICDISER.ICDISER1 |= (1 << 25); //ʹ��57���ж� ���
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & (~(0xff << 8)))
			| (0b00000001 << 8); //���ж�57 �͵� cpu0

	//---------------------key3------------------------------------

	GPX1.CON |= (0xf << 8); //����Ϊ�ⲿ�ж�ģʽ
	EXT_INT41_CON = (EXT_INT41_CON & (~(0XF << 8))) | (0X2 << 8); //���� �½����źŴ����ж�

	EXT_INT41_FLTCON0 |= 1 << 23;
	EXT_INT41_FLTCON0 &= ~(1 << 22); //������ѡ�񲻾�׼��ʱ�˲�

	EXT_INT41_MASK &= ~(1 << 2); //ʹ���жϴ��ݵ� GIC

	//26  58  �C  EINT[10]
	fun_p[58] = key3_int;

	ICDISER.ICDISER1 |= (1 << 26); //ʹ��58���ж� ���
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & (~(0xff << 16)))
			| (0b00000001 << 16); //���ж�58 �͵� cpu0

	ICDDCR = 1; //���� ��������ж�

	CPU0.ICCICR = 1; //ʹ��icc

}

void eint16_31_int() {

	if (EXT_INT43_PEND & (1 << 2)) {
		timer4_start(50, 4);

		EXT_INT43_PEND = (1 << 2); // ����ж�Դ
	} else if (0) {

	}
	ICDICPR.ICDICPR1 = (1 << 26); //����жϻ����ICD
}

void key4_init() {

	timer4_open();

	GPX3.CON |= (0xf << 8); //����Ϊ�ⲿ�ж�ģʽ
	EXT_INT43_CON = (EXT_INT43_CON & (~(0XF << 8))) | (0X2 << 8); //���� �½����źŴ����ж�

	EXT_INT43_FLTCON0 |= 1 << 23;
	EXT_INT43_FLTCON0 &= ~(1 << 22); //������ѡ�񲻾�׼��ʱ�˲�

	EXT_INT43_MASK &= ~(1 << 2); //ʹ���жϴ��ݵ� GIC

	//32  64  �C  EINT16_31[26]
	fun_p[64] = eint16_31_int;

	ICDISER.ICDISER2 |= (1 << 0); //ʹ��64���ж� ���
	ICDIPTR.ICDIPTR16 = (ICDIPTR.ICDIPTR16 & (~(0xff << 0)))
			| (0b00000001 << 0); //���ж�64 �͵� cpu0

	ICDDCR = 1; //���� ��������ж�

	CPU0.ICCICR = 1; //ʹ��icc

}
