import serial
import time
import sys
from datetime import datetime

ff = open("/var/vehiscan/trigger/log3.txt",'r')
line = ff.readline()
if(line=="" or line=="\n"):
	sys.exit(0)


sr = serial.Serial(port="/dev/ttyS0",baudrate=9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS)
time.sleep(2)
sr.write(b"ABC")
time.sleep(2)
sr.write(b"O")
time.sleep(2)
sr.write(b"ABC")
time.sleep(2)
sr.write(b"\x01")
sr.write(b"\x00")
sr.write(b"<S0>")

tt = open("timelog.txt",'w')
tt.write(str(datetime.now()))
tt.close()

def send(vehicle, speed):
	sr.write(vehicle.encode() + b"-" + speed.encode() + b"  ")

vals = line[:-1].split(" ")

vehiclenum = vals[0]
speed = vals[1]
print(vehiclenum, speed)
send(vehiclenum, speed)

ff.close()

#ff = open("/var/vehiscan/trigger/log3.txt",'w')
#ff.close()

sr.write(b"<FZ><FX>")
sr.close()

