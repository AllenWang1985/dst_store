#include <iostream>

using namespace std;

#define MAX(a,b)    (a>b)?a:b

int main()
{
    int a = 1;
    int b = 2;
    int max = MAX(a,++a);
    cout << "1��2�ĸ���"<< max <<endl;
    cout << "Hello world!" << endl;
    return 0;
}
