#include <iostream>

using namespace std;

class myclass {
public:
    int sum;
    void sum_it(int x);
};

void myclass::sum_it(int x)
{
    int i;
    sum = 0;
    for(i = x; i; i--) sum += i;
}

int main()
{
    int myclass::*dp;        //ָ�� myclass ���������ͳ�Ա������ָ��
    void (myclass::*fp)(int x);        //ָ��myclass �г�Ա������ָ��
    myclass c;
    dp = &myclass::sum;        //��ó�Ա�����ĵ�ַ
    fp = &myclass::sum_it;    //��ó�Ա�����ĵ�ַ
    (c.*fp)(7);       //���� 1 �� 7 ��ӵĺ�
    cout << "summation of 7 is " << c.*dp;

    return 0;
}
