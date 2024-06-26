import RPi.GPIO as GPIO
import time

a_led = 26
b_led = 19
c_led = 13
d_led = 6
e_led = 5
f_led = 22
g_led = 27
btn = 21

GPIO.setmode(GPIO.BCM)

GPIO.setup(a_led, GPIO.OUT)
GPIO.setup(b_led, GPIO.OUT)
GPIO.setup(c_led, GPIO.OUT)
GPIO.setup(d_led, GPIO.OUT)
GPIO.setup(e_led, GPIO.OUT)
GPIO.setup(f_led, GPIO.OUT)
GPIO.setup(g_led, GPIO.OUT)

GPIO.setup(btn, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

leds = [a_led, b_led, c_led, d_led, e_led, f_led, g_led]

seg_patterns = [
	[0,0,0,0,0,0,1], #0
	[1,0,0,1,1,1,1], #1
	[0,0,1,0,0,1,0], #2
	[0,0,0,0,1,1,0], #3
	[1,0,0,1,1,0,0], #4
	[0,1,0,0,1,0,0], #5
	[0,1,0,0,0,0,0], #6
	[0,0,0,1,1,1,1], #7
	[0,0,0,0,0,0,0], #8
	[0,0,0,0,1,0,0],] #9

count_1 = 0

try:
	while True:
		if GPIO.input(btn) == True:
			i = 0

			for i in range(6):
				GPIO.output(leds[i], seg_patterns[count_1][i])

			count_1 = count_1 + 1
			print(count_1)
			time.sleep(1)

		if count_1 == 10:
			count_1 = 0

except KeyboardInterrupt:
	GPIO.cleanup()
