import RPi.GPIO as GPIO
import time

switch = 6
r_led = 21
b_led = 12
g_led = 25
count = 0

GPIO.setmode(GPIO.BCM)
GPIO.setup(switch, GPIO.IN)

GPIO.setup(r_led, GPIO.OUT)
GPIO.setup(g_led, GPIO.OUT)
GPIO.setup(b_led, GPIO.OUT)

try:
	while True:
		if GPIO.input(switch) == True:
			count = count + 1
			while count == 1:
				GPIO.output(r_led, False)
				GPIO.output(g_led, True)
				GPIO.output(b_led, True)
				time.sleep(0.5)
				if GPIO.input(switch) == False:
					count = count + 1
					print("red")
					print(count)

			while count == 2:
				GPIO.output(r_led, True)
				GPIO.output(g_led, False)
				GPIO.output(b_led, True)
				time.sleep(0.5)
				if GPIO.input(switch) == False:
					count = count + 1
					print("Green")
					print(count)

			while count == 3:
				GPIO.output(r_led, True)
				GPIO.output(g_led, True)
				GPIO.output(b_led, False)
				time.sleep(0.5)
				if GPIO.input(switch) == False:
					count = count + 1
					print("Blue")
					print(count)

			while count == 4:
				GPIO.output(r_led, True)
				GPIO.output(g_led, True)
				GPIO.output(g_led, True)
				time.sleep(0.5)
				if GPIO.input(switch) == False:
					count = 0
					print("Off")
					print(count)

except KeyboardInterrupt:
	GPIO.cleanup()
