#include <iostream>
#include <iomanip>
#include <stdio.h>
/*
 C++��ͷ�ļ�����.h
 std ��׼�����ռ�
 :: �������޶���
 >> ���붨��
 << �������
 using
 using namespace
 C��׼���ͷ�ļ�����һ�㲻��.h
 printfҲ������
 ����������ʹ��ʱ���壬ֻ�ڸ�������Ч
 setw(10)ֻ��������������10����
      ��ʾ�ճ�һ�Σ�����10�����ַ��ռ䣬����<<��������δӺ���ǰ�Ž�ȥ
*/

//using std::cout;
//using std::endl;

using namespace std;

int main()
{
//    std::cout << "Hello World!" << std::endl;
    cout << "Hello World" << endl;
    printf("Hello World \n");
    cout << setw(10) << "123456789" << endl;
    return 0;
}
