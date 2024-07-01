import sys
import RPi.GPIO as GPIO
import time

from PyQt5.QtWidgets import *
from PyQt5 import uic
from PyQt5.QtCore import Qt

form_class = uic.loadUiType("./")[0]

log_num = 0
sensor_pin = 18

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN)
dhtDevice = adafruit_dht.DHT11(board.D18)

class WindowClass(QMainWindow, form_class):

def temhum (self):
	temp = dhtDevice.Temperature
	humid = dhtDevice.humidity
	print(f'{log_num} - Temp : {temp}c / Humid : {humid}%')
	log_num += 1
	time.sleep(2<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <widget name="__qt_fake_top_level">
  <widget class="QLCDNumber" name="lcdNumber">
   <property name="geometry">
    <rect>
     <x>140</x>
     <y>32</y>
     <width>111</width>
     <height>41</height>
    </rect>
   </property>
  </widget>
 </widget>
 <resources/>
</ui>



if __name__ == "__main__" :
	app = QApplication(sys.argv)
	myWindow = WindowClass()
	myWindow.show
	app.exec_()	
