#include <iostream>

using namespace std;

class A {
public:
    virtual void fun()=0;
};
class B {
public:
    void fun(){
        cout << "B������д���ࣨA���Ĵ��麯��" << endl;
    }
};

int main()
{
    B b;
    b.fun();
    cout << "Hello world!" << endl;
    return 0;
}

