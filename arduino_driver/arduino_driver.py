#!/usr/bin/env python
import roslib; 
import rospy
from std_msgs.msg import UInt16
import serial
data_in = 0
inbyte = 0

def head_turn(data):
	ser.write('/3/2/'+str(data)+'/')

def mov_drive(data):
	if(data <= 360 ):
		ser.write('/3/1/'+str(data)+'/')

def main_sonar()
		ser.write('/3/1/'+str(data)+'/')
	
def init_serial():
	ser = serial.Serial('/dev/ttyACM0', 9600)
	
def serial_read_to_publisher():
	serial_protocol_decode()
	# if(data_in == 1):
		
	# if(data_in == 2):

	# if(data_in == 3):
	
	if data_in == 4: #sonar
		serial_protocol_decode()
		if data_in == 1:
			serial_protocol_decode()
			sonar.publish(data_in)
			
		
def serial_protocol_decode():
	data_in = 0
	while inbyte != '/':
		inbyte = ser.read()
		if inbyte > 0 and inbyte != '/':
			data_in = data_in *10 + inbyte - '0'
	
	return data_in
	
def driver():
	init_serial()
    rospy.init_node('arduino_driver', anonymous=True)
    rospy.Subscriber("movement", UInt16, mov_drive)
	rospy.Subscriber("head_turn", UInt16, head_turn)
	data_in = rospy.Publisher('sonar', UInt16)
	serial_read_to_publisher()
    rospy.spin()


if __name__ == '__main__':
    driver()