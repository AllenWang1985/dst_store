#include <iostream>

using namespace std;

template <typename N>

void maopao(N a[],int len)
{
    N temp;
    int i;
    int j;
    for(i = 0;i < (len-1); i++)
    {
        for(j = 0;j<(len-i-1);j++)
        {
            if(a[j]>a[j+1])//���ں�Ϊ��ֵ�������ð�ݣ���Ϊ����
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    for(i=0; i<len; i++)
    {
        cout << a[i] << " ";
    }
    cout <<endl;
}

template <typename N>

void remaopao(N a[],int len)
{
    N temp;
    int i;
    int j;
    for(i = 0;i < (len-1); i++)
    {
        for(j = 0;j<(len-i-1);j++)
        {
            if(a[j]<a[j+1])//С�ں�Ϊ��ֵ�������ð�ݣ���Ϊ����
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    for(i=0; i<len; i++)
    {
        cout << a[i] << " ";
    }
    cout <<endl;
}



int main()
{
    //int����
    int a[10] = {13,12,17,18,19,110,11,16,15,14};
    maopao<int>(a,10);
    remaopao<int>(a,10);
    //char����
    char b[10] = {'B','S','C','A','Q','D','F','G','H','J'};
    maopao<char>(b,10);
    remaopao<char>(b,10);
    //float����
    float c[10] = {1.3,1.2,1.7,1.8,1.9,1.1,2.8,1.6,1.5,1.4};
    maopao<float>(c,10);
    remaopao<float>(c,10);
    //double����
    double d[10] = {1.3,1.2,1.7,1.8,1.9,1.1,2.8,1.6,1.5,1.4};
    maopao<double>(d,10);
    remaopao<double>(d,10);
    cout << "Hello world!" << endl;
    return 0;
}

