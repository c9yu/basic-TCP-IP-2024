import RPi.GPIO as GPIO
import time

# 세븐 세그먼트 디스플레이의 핀 설정
segments = [26, 25, 13, 6, 5, 22, 27] # a, b, c, d, e, f, g
digits = [12, 18, 17, 16] # COM1, COM2, COM3, COM4

# 세그먼트에 출력할 숫자의 세그먼트 패턴
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

GPIO.setmode(GPIO.BCM)
for segment in segments:
    GPIO.setup(segment, GPIO.OUT)
    GPIO.output(segment, 0)
for digit in digits:
  GPIO.setup(digit, GPIO.OUT)
  GPIO.output(digit, 1)

#GPIO.setmode(GPIO.BCM)
#GPIO.setup(segments, GPIO.OUT)
#GPIO.setup(digits, GPIO.OUT)

#digit = 0

def display_digit(com, digit):
	for i in range(0, 4):
		if i == com:
			GPIO.output(digits[i], True)
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

try:
	while True:
		count = 0
		for i in range(0, 9999):
			start_time = time.time()
			while time.time() - start_time < 1:
				display_number(i)
			if i == 9999:
				i = 0
		
except KeyboardInterrupt:
    GPIO.cleanup()

