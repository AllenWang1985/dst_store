@echo off
echo -------------------------------------------------------
echo 1. Ĭ�Ϸ����ֻ� /sdcard/Download/ Ŀ¼��
echo 2. �ļ�·���в�Ҫ������
echo -------------------------------------------------------
echo.
set /p PUSH_FILE=����ļ��Ͻ�������ʾ�������س�:
echo.
adb push -p %PUSH_FILE% /sdcard/Download/
echo.
pause