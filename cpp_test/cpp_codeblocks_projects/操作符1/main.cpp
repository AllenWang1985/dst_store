#include <iostream>

using namespace std;

class A{
public:
    int i;
    A(){
        i = 100;
    }
    A(int ii){
        i = ii;
    }
};

int main()
{
    A a(200);
    A *a1 = new A();
    int A::* p;//ָ����A��int�ͳ�Ա������ָ��
    p = &A::i;//����A�г�Ա����i�ĵ�ַ(��ʵ�ǵ�ַƫ����)����p
    cout << "p = " << p << endl;
    cout << a.*(&A::i) << endl;

    cout << a1->*p << endl;
    delete a1;
    cout << "Hello world!" << endl;
    return 0;
}
