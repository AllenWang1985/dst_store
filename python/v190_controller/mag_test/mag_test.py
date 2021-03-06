import serial
import array
import os
import signal
from time import sleep
import time

def onsignal_int(a,b):
    print "sigint!"
    global ser
    if ser.isOpen():
    	ser.write(stop_data_transfer_cmd)
    	sleep(0.05)
    	ser.write(led_off_cmd)
        ser.close()

signal.signal(signal.SIGINT, onsignal_int)
signal.signal(signal.SIGTERM, onsignal_int)


all_data_transfer_cmd="Mag Data Transfer"
stop_data_transfer_cmd="Stop Data Transfer"
get_sn_cmd="Get SN Param"
led_on_cmd="LED On"
led_off_cmd="LED Off"

# Settings
MAX_COUNT = 1
TEST_COUNT_MAX = 500
comport = 'COM4'
LOG_FILE = "mag_test_log.txt"

# init log
f = open(LOG_FILE, "w")
f.write("-------------------------------------------------------\n")
f.write("start time:"+time.strftime("%H:%M:%S")+"\n")

# init serial
ser = serial.Serial()

print "--------------------Test Start--------------------"

count = 0
error_count = 0
while count < MAX_COUNT:
    count = count+1

    print "--------------------"
    print "["+time.strftime("%H:%M:%S")+"]Run "+str(count)+" time."
    print "--------------------"
    f.write("-------------------------------------------------------\n")
    f.write("["+time.strftime("%H:%M:%S")+"]Run "+str(count)+" time.\n")

    # Testing ...

    # open serial
    ser.port = comport
    ser.baudrate = 115200
    ser.rts = False
    ser.timeout = 5
    ser.open()

    if ser.isOpen():
        print "Open "+comport+" succeeded."

        #led on
        ser.write(led_on_cmd)
        sleep(0.05) 

        ser.write(get_sn_cmd)
        sleep(0.05) 
        sn_num = ser.read(16)[2:]
        print "SN : " + sn_num
        f.write(time.strftime("%H:%M:%S")+"\n") 
        f.write("SN : "+sn_num+"\n")
        f.write("-------------------------"+"\n") 

        #mag test
        ser.write(stop_data_transfer_cmd)
        sleep(0.05)
        ft = open(str(count)+".log", "w")
        ser.write(all_data_transfer_cmd)
        test_count = 0
        while test_count < TEST_COUNT_MAX:
            mag_data = ser.read(9)
            if 0x08 == int(ord(mag_data[0])) and 0x00 == int(ord(mag_data[1])):
                pass
            else:
                print 'ERR HEADER FAIL!'
                continue
            crc = 0 ^int(ord(mag_data[2])) ^ int(ord(mag_data[3])) ^ int(ord(mag_data[4])) ^ int(ord(mag_data[5])) ^ int(ord(mag_data[6])) ^ int(ord(mag_data[7]))
            if int(crc) != int(ord(mag_data[8])) :
                print "ERR [CRC Failed] x:%02x:%02x,y:%02x:%02x,z:%02x:%02x,crc:%02x:%02x"%ord(mag_data[3]),ord(mag_data[4]),ord(mag_data[5]),ord(mag_data[6]),ord(mag_data[7]),(ord(mag_data[-1]),crc)
                continue
            if ord(mag_data[3]) != 0 :
                mag_data_x = ord(mag_data[3])*0x100 + ord(mag_data[4])
            else:
                mag_data_x = ord(mag_data[4])
            if ord(mag_data[5]) != 0 :
                mag_data_y = ord(mag_data[5])*0x100 + ord(mag_data[6])
            else:
                mag_data_y = ord(mag_data[6])
            if ord(mag_data[7]) != 0 :
                mag_data_z = ord(mag_data[7])*0x100 + ord(mag_data[8])
            else:
                mag_data_z = ord(mag_data[8])
            if mag_data_x > 0x8000:
                mag_data_x = (0x10000 - mag_data_x) * -1
            if mag_data_y > 0x8000:
                mag_data_y = (0x10000 - mag_data_y) * -1
            if mag_data_z > 0x8000:
                mag_data_z = (0x10000 - mag_data_z) * -1
            mag_view = str(test_count)+",["+time.strftime("%H:%M:%S")+"],"
            mag_view += "x:%f,y:%f,z:%f"%(mag_data_x*0.0015,mag_data_y*0.0015,mag_data_z*0.0015)
            #mag_view = "[status:%02x] x:%02x:%02x,y:%02x:%02x,z:%02x:%02x" %(ord(mag_data[0]),ord(mag_data[3]),ord(mag_data[4]),ord(mag_data[5]),ord(mag_data[6]),ord(mag_data[7]),ord(mag_data[8]))
            ft.write(mag_view+"\n") 
            print mag_view
            test_count += 1
        ser.write(stop_data_transfer_cmd)
        ft.close()

        #led off
        sleep(0.05)
        ser.write(led_off_cmd)

        # Test end
        ser.close()
        f.flush()
        print "Close "+comport
    else:
        print "Error: open "+comport+" failed!"

print "--------------------"
f.write("-------------------------------------------\n")
print "All : " + str(count) + " time"
f.write("All : " + str(count) + " time\n")
print "Error : " + str(error_count) + " time"
f.write("Error : " + str(error_count) + " time\n")
f.flush()
sleep(0.01)
f.close()
print "Close " + LOG_FILE
print "--------------------Test End--------------------"
