from datetime import datetime
from datetime import timedelta
import sys
import serial
import time

tt = open('timelog.txt','r')
line = tt.readline()[:-1]
tt.close()
if(line==""):
	sys.exit(0)
date = datetime.strptime(line, "%Y-%m-%d %H:%M:%S.%f")

diff = datetime.now() - date
print(diff)

if(diff > timedelta(minutes=1)):
	tt = open('timelog.txt','w')
	tt.close()
	sr = serial.Serial(port="COM3",baudrate=19200,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS)
	sr.write(b"ABC")
	time.sleep(2)
	sr.write(b"O")
	time.sleep(1)
	sr.write(b"ABC")
	sr.write(b"\x01")
	sr.write(b"\x00")
	sr.write(b"<F6> <F6>")
	sr.write(b"<FZ><FX>")
	sr.close()
	


