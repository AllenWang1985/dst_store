#include <iostream>  
#include <windows.h>  
using namespace std;  
  
#define BUF_SIZE 1024  
char szName[] = "testmap";    // �����ڴ������  

void LockMutex(HANDLE m_hMutex)
{
    DWORD dRes = -1;
    dRes = WaitForSingleObject(m_hMutex, INFINITE);
    if(WAIT_OBJECT_0  == dRes) cout<<"�����ɹ�!"<<endl;
    else if(WAIT_ABANDONED == dRes) cout<<"������������"<<endl;
    else if(WAIT_TIMEOUT == dRes) cout<<"�ȴ���ʱ"<<endl;
    else if(WAIT_FAILED == dRes) cout<<"��������"<<endl;
    else cout<<"����ʧ��!"<<endl;
}

int main()  
{
    char szInfo[BUF_SIZE] = {0};

    // ���������ļ����  
    HANDLE hMapFile = CreateFileMapping(  
        INVALID_HANDLE_VALUE,    // �����ļ����  
        NULL,                    // Ĭ�ϰ�ȫ����  
        PAGE_READWRITE,          // �ɶ���д  
        0,                       // ��λ�ļ���С  
        BUF_SIZE,                // ��λ�ļ���С  
        szName          // �����ڴ�����  
        );  

    char *pBuf = (char *)MapViewOfFile(  
        hMapFile,            // �����ڴ�ľ��  
        FILE_MAP_ALL_ACCESS, // �ɶ�д���  
        0,  
        0,  
        BUF_SIZE  
        );  

    // ���������
    HANDLE mutex;
	char mutexname[] = "testmapmutex";
    mutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE,mutexname);
    if(mutex == NULL)  
    {
        mutex = CreateMutex(NULL,FALSE,mutexname);  
    }
    
    while(1)  
    {
        cout << "input..." << endl;
        gets(szInfo); // ��ʵgets������ȫ  
        LockMutex(mutex);
        memset(pBuf, 0, BUF_SIZE);
        strncpy(pBuf, szInfo, BUF_SIZE);
        //strncpy(pBuf, "debug", 5);
        ReleaseMutex(mutex);cout<<"�������!"<<endl;
    }  
  
    UnmapViewOfFile(pBuf);  
    CloseHandle(hMapFile);  
    return 0;  
}  
