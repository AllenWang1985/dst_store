@echo off

set /p NUM=������������:

for /f "tokens=2 delims==" %%a in ('wmic path win32_operatingsystem get LocalDateTime /value') do (
  set today=%%a
)
set Today_All=%today:~0,14%
set Today_Day=%today:~0,8%
set Today_Time=%today:~8,6%
set LOG_PATH=.\logs\%NUM%#_%Today_Day%_%Today_Time%


rem MKDIR
if not exist .\logs (
	mkdir .\logs
)
if not exist %LOG_PATH% (
	mkdir .\%LOG_PATH%
)

adb root
adb pull -p /sdcard/logs/ .\%LOG_PATH%

echo.
echo.
echo.
echo �����Ŀ���ʱ�����£�
adb shell uptime
echo.
echo.
echo.
pause