@echo off
adb shell dumpsys battery
echo -------------------------------
echo �����ٷֱȣ�
adb shell cat /sys/class/power_supply/battery/capacity
echo.
pause