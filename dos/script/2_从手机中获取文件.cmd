@echo off
echo ----------------------------------------------
echo 1. Ĭ�ϴ��ֻ� /sdcard/Download/ Ŀ¼��ץȡ�ļ�
echo 2. �������ֻ�����
echo ----------------------------------------------
echo.
echo �ֻ�/sdcard/Download/·���µ����ļ��У�
echo.
adb shell ls /sdcard/Download/
echo.
echo ----------------------------------------------
echo.
set /p PULL_FILE=������ץȡ�ļ�������:
echo.
adb pull -p /sdcard/Download/%PULL_FILE% .\
pause