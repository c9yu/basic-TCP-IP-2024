import sys
import RPi.GPIO as GPIO
import time
from PyQt5. QtWidgets import *
from PyQt5 import uic
from PyQt5.QtCore import Qt

def measure():
  GPIO.output(trig, True)        # 10us 동안 high레벨로 triger를 >
  time.sleep(0.00001)
  GPIO.output(trig, False)
  start = time.time()                 # 현재 시간 저장

  while GPIO.input(echo) == False: # echo가 없으면
    stop = time.time()                # 현재 시간을 start 변수에 저[>
  while GPIO.input(echo) == True:  # echo가 있으면
    stop = time.time()                # 현재시간을 stop 변수에 저장
  elapsed = stop - start              # 걸린 시간을 구하고
  distance = (elapsed * 19000) / 2    # 초음파 속도를 이용해서 거리[>

  return distance 

def display_digit(com, digit):
	for i in range(0,4):
		if i == com:
			GPIO.output(digits[i],True)
		else:
			GPIO.output(digits[i], False)

	for j in range(0,7):
		GPIO.output(segments[j], num[digit][j])

def display_number(numbers):
	numbers_1 = numbers // 1000
	numbers_2 = (numbers % 1000) // 100
	numbers_3 = (numbers % 100) // 10
	numbers_4 = numbers % 10

	display_digit(0, numbers_1)
	time.sleep(0.0001)
	display_digit(1, numbers_2)
	time.sleep(0.0001)
	display_digit(2, numbers_3)
	time.sleep(0.0001)
	display_digit(3, numbers_4)
	time.sleep(0.0001)

form_class = uic.loadUiType("./test.ui")[0]

leds = [19, 20, 21]
echo = 24
trig = 23
piezoPin = 4
melody = [130.81, 146.83, 164.81, 174.61, 196, 220, 246.94, 261.63]
segments = [26, 25, 13, 6, 5, 22, 27]
digits = [12, 18, 17, 16]

num = [[0,0,0,0,0,0,1],
			 [1,0,0,1,1,1,1],
			 [0,0,1,0,0,1,0],
			 [0,0,0,0,1,1,0],
			 [1,0,0,1,1,0,0],
			 [0,1,0,0,1,0,0],
			 [0,1,0,0,0,0,0],
			 [0,0,0,1,1,1,1],
			 [0,0,0,0,0,0,0],
			 [0,0,0,0,1,0,0]]

#setmode, setup
#LED
GPIO.setmode(GPIO.BCM)
for led in leds:
	GPIO.setup(led, GPIO.OUT)
	GPIO.output(led, 0)

# 초음파 센서
GPIO.setup(echo,GPIO.IN)
GPIO.setup(trig,GPIO.OUT)

# 부저
GPIO.setup(piezoPin,GPIO.OUT)
Buzz = GPIO.PWM(piezoPin,440)

#세븐세그먼트
for segment in segments:
	GPIO.setup(segment, GPIO.OUT)
	GPIO.output(segment, 0)
for digit in digits:
	GPIO.setup(digit, GPIO.OUT)
	GPIO.output(digit, 1)

class WindowClass(QMainWindow, form_class):
	def __init__(self):
		super().__init__()
		self.setupUi(self)

		self.btn_r.clicked.connect(self.btn_r_func)
		self.btn_g.clicked.connect(self.btn_g_func)
		self.btn_b.clicked.connect(self.btn_b_func)
		self.btn_off.clicked.connect(self.btn_off_func)
		self.btn_ultra.clicked.connect(self.btn_ultra_func)
		self.btn_mel.clicked.connect(self.btn_mel_func)
		self.btn_count.clicked.connect(self.btn_count_func)

	def btn_r_func(self):
#		print("r") : 연결 확인용
		GPIO.output(leds[0], False)
		GPIO.output(leds[1], True)
		GPIO.output(leds[2], True)

	def btn_g_func(self):
		GPIO.output(leds[0], True)
		GPIO.output(leds[1], False)
		GPIO.output(leds[2], True)

	def btn_b_func(self):
		GPIO.output(leds[0], True)
		GPIO.output(leds[1], True)
		GPIO.output(leds[2], False)

	def btn_off_func(self):
		GPIO.output(leds[0], True)
		GPIO.output(leds[1], True)
		GPIO.output(leds[2], True)
		Buzz.stop()

	def btn_ultra_func(self):
		distance_cm = measure()
		print("Distance: %.2f cm" %distance_cm)

		self.distance.display(distance_cm)

	def btn_mel_func(self):
		Buzz.start(10)
		for i in range(0, len(melody)):
			Buzz.ChangeFrequency(melody[i])
			time.sleep(0.3)
		Buzz.stop()
		time.sleep(1)

	def btn_count_func(self):
		while True:
			for i in range(0, 9999):
				start_time = time.time()
				while time.time() - start_time < 1:
					display_number(i)
				if i == 9999:
					i = 0

	def keyPressEvent(self, event):
		Buzz.start(10)
		if event.key() == Qt.Key_1:
			Buzz.ChangeFrequency(melody[0])
			time.sleep(0.1)

		if event.key() == Qt.Key_2:
			Buzz.ChangeFrequency(melody[1])
			time.sleep(0.1)

		if event.key() == Qt.Key_3:
			Buzz.ChangeFrequency(melody[2])
			time.sleep(0.1)

		if event.key() == Qt.Key_4:
			Buzz.ChangeFrequency(melody[3])
			time.sleep(0.1)

		if event.key() == Qt.Key_5:
			Buzz.ChangeFrequency(melody[4])
			time.sleep(0.1)

		if event.key() == Qt.Key_6:
			Buzz.ChangeFrequency(melody[5])
			time.sleep(0.1)

		if event.key() == Qt.Key_7:
			Buzz.ChangeFrequency(melody[6])
			time.sleep(0.1)

		if event.key() == Qt.Key_8:
			Buzz.ChangeFrequency(melody[7])
			time.sleep(0.1)

	def keyReleaseEvent(self,event):
		if event.key() in [Qt.Key_1, Qt.Key_2, Qt.Key_3, Qt.Key_4, Qt.Key_5, Qt.Key_6, Qt.Key_7, Qt.Key_8]:
			Buzz.stop()

if __name__ == "__main__":
	app = QApplication(sys.argv)
	myWindow = WindowClass()
	myWindow.show()
	app.exec_()
