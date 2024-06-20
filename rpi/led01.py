import RPi.GPIO as GPIO
import time

r_led = 21
b_led = 12
g_led = 25

#GPIO를 BCM모드로 설정
GPIO.setmode(GPIO.BCM)
#GPIO핀 설정 (입력/출력)
GPIO.setup(r_led, GPIO.OUT)
GPIO.setup(g_led, GPIO.OUT)
GPIO.setup(b_led, GPIO.OUT)


try:
	while (True):
		GPIO.output(r_led, False)
		GPIO.output(g_led, True)
		GPIO.output(b_led, True)
		time.sleep(1)

		GPIO.output(r_led, True)
		GPIO.output(g_led, False)
		GPIO.output(b_led, True)
		time.sleep(1)

		GPIO.output(r_led, True)
		GPIO.output(g_led, True)
		GPIO.output(b_led, False)
		time.sleep(1)

except KeyboardInterrupt: #Ctrl + c
	GPIO.cleanup()
