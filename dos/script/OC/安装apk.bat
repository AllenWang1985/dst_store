@echo off
adb root
set /p APK_PATH=��apk�Ͻ�cmd����:
echo.
adb install -r -g %APK_PATH%
echo.
echo ����ʾSuccess,��װ�ɹ������������°�װ
pause