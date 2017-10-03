#include <stdio.h>;
#include <string.h>;
//#include <stdarg.h>;

typedef char * va_list;

#define _INTSIZEOF(n) ((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1) )

#define va_start(ap,v) ( ap = (va_list)&v + _INTSIZEOF(v) )

#define va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )

#define va_end(ap) ( ap = (va_list)0 )

/* ANSI��׼��ʽ��������ʽ�������ڵ�ʡ�Ժű�ʾ��ѡ���� */

int demo(char *msg, ... )
{
    va_list argp;                   /* ���屣�溯�������Ľṹ */
    int argno = 0;                  /* ��¼�������� */
    char *para;                     /* ���ȡ�����ַ������� */

/* argpָ����ĵ�һ����ѡ������msg�����һ��ȷ���Ĳ��� */
    va_start( argp, msg );

    while (1)
    {
        para = va_arg( argp, char *);  /*ȡ����ǰ�Ĳ���������Ϊchar *. */
        if ( strcmp( para, "\0") == 0 )/* ���ÿմ�ָʾ����������� */
            break;
        printf("Parameter #%d is: %s \n", argno, para);
        argno++;
    }
    va_end( argp ); /* ��argp��ΪNULL */
    return 0;
}


int main( void )
{
    demo("DEMO", "This", "is", "a", "demo!" ,"333333", "\0");
    return 0;
}
