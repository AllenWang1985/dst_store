#include <iostream>

using namespace std;
//C++��������ռλ��������ռλ������һ�����ڳ�����չ�Ͷ�C����ļ���
int func(int a, int b, int =0)
{
  return a + b;
}
//Ĭ�ϲ�
void fun1(int a = 0,int b =0)
{
    cout << "void fun1(int a = 0,int b =0)" << endl;
    cout << "a = "<< a << " b = "<< b << endl;
}
//ռλ��
void fun2(int ,int )
{
    cout << "void fun2(int ,int )" << endl;
}

int main()
{
    //���Ĭ�ϲ�����ռλ������һ�𣬶��ܵ�������
    func(1, 2);
    func(1, 2, 3);
    fun1();
    fun1(1);
    fun1(1,2);
    fun2(1,2);
    cout << "Hello world!" << endl;

    return 0;
}
