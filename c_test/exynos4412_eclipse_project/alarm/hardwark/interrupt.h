#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "exynos_4412.h"

extern void (*fun_p[160])(); //�жϺ���ָ�����飬���жϺ�����ڵ�ַ��

extern void do_irq(void);

#endif
