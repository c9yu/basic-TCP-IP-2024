import RPi.GPIO as GPIO
import time

pirPin = 24
g_led = 25
r_led = 21

GPIO.setmode(GPIO.BCM)
GPIO.setup(pirPin, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(r_led, GPIO.OUT)
GPIO.setup(g_led, GPIO.OUT)

try:
	while True:
		if GPIO.input(pirPin) == True:
			GPIO.output(r_led, True)
			GPIO.output(g_led, False)
			print("사람 있음")
		else:
			GPIO.output(r_led, False)
			GPIO.output(g_led, True)
			print("사람 없음")

except KeyboardInterrupt:
	GPIO.cleanup()
