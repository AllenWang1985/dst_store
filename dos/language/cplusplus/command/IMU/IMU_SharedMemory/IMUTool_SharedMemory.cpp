#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>

#define DEBUG_ENABLE 0
#define BUF_SIZE 1024
char szName[] = "testmap";    // �����ڴ������

void LockMutex(HANDLE m_hMutex)
{
    DWORD dRes = -1;
    dRes = WaitForSingleObject(m_hMutex, INFINITE);
#if DEBUG_ENABLE
    if(WAIT_OBJECT_0  == dRes) printf("�����ɹ�!\n");
    else if(WAIT_ABANDONED == dRes) printf("������������!\n");
    else if(WAIT_TIMEOUT == dRes) printf("�ȴ���ʱ!\n");
    else if(WAIT_FAILED == dRes) printf("��������!\n");
    else printf("����ʧ��!\n");
#endif
}

int main(int argc, const char* argv[])
{
	FILE* pipe = NULL;
	char ch = 0;
	int count = 0;
    unsigned int line_num = 0;
	char buffer[BUF_SIZE];
    char temp_buffer[BUF_SIZE];
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
    
	pipe = _popen("adb shell imutool", "r");
	if (!pipe) return -1;//����0��ʾ����ʧ��

    printf("No,Time (s),Temperature (C),Gyro_x,Gyro_y,Gyro_z,Accel_x,Accel_y,Accel_z,Mag_x,Mag_y,Mag_z\n");
	while(!feof(pipe))
	{
        memset(buffer, 0, sizeof(buffer));
		while('\n' != ch)
		{
            ch = fgetc(pipe);
            if ('\t' == ch) ch = ',';
			buffer[count++] = ch;
		}
        ch =0;
		count = 0;

        printf("%d,%s", line_num, buffer);
        memset(temp_buffer, 0, BUF_SIZE);
        sprintf(temp_buffer, "%d,%s", line_num++, buffer);
        
        LockMutex(mutex);
        memset(pBuf, 0, BUF_SIZE);
        strcpy(pBuf, temp_buffer);
        ReleaseMutex(mutex);

#if DEBUG_ENABLE
        printf("�������!\n");
#endif

	}
	_pclose(pipe);

	getchar();
	return 0;
}

