@echo off
echo (��������ͷ��������)
echo �鿴ͷ���Ѱ󶨵��ֱ���MAC��ַ
echo -------
adb shell cat persist/remote_pairing/factory_pairing.txt
echo -------
adb shell getprop persist.remote1
echo -------
pause