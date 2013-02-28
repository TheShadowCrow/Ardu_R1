#!/usr/bin/env python
import roslib; 
import rospy
from lxml import etree

def readprotocol(protocol):
	doc = etree.parse(protocol)
	

if __name__ == '__main__':
	