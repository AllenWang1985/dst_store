 @echo off
 set /a tp_num=0 
 
:_start_get_tp_log
	echo ============ ����ץȡ tp log ... ====================
	rem ��ʱ2�룬ȷ��adb�������
	ping -n 2 127.0.0.1 > nul
	rem ȷ���Ƿ������ֻ�
	adb devices 
	adb root
	adb remount
	rem ����Ƿ�Ϊfocaltech
	adb shell cat /proc/tp_info
	adb shell cat /sys/bus/i2c/devices/3-0038/fts_dump_reg || goto _warning_log
	
	rem adb shell "echo /system/etc/Conf_MultipleTest.ini > /sys/bus/i2c/devices/3-0038/fts_test"
	
	echo ==����Cit�н����Լ��������tp�Ѿ��Լ죬���Ըò��裩==
	echo ============ �Լ���ɺ󣬰���������� ===============
	pause
	mkdir tp_log%tp_num%
	adb shell "cd /sdcard/ && mkdir tp_log && cp result_* tp_log -a"
	adb pull /sdcard/tp_log ./tp_log%tp_num%
	adb shell "cd /sdcard/ && rm tp_log -rf"
	set /a tp_num+=1
	echo ============ ���ֻ���tp logץȡ��� =================
	echo ============ �뻻��һ���ֻ� =========================
	pause
	goto _start_get_tp_log
:_warning_log
	echo ============ [Warning] TP����focaltech��adb����ʧ��! ==============
	set /p input="Continue?(y/n)" 
	if not "%input%"=="n" (
		goto _start_get_tp_log
	) else (
		exit
	)