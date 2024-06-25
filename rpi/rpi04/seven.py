import RPi.GPIO as GPIO
import time

a_led = 26
b_led = 19
c_led = 13
d_led = 6
e_led = 5
f_led = 22
g_led = 27

GPIO.setmode(GPIO.BCM)

GPIO.setup(a_led, GPIO.OUT)
GPIO.setup(b_led, GPIO.OUT)
GPIO.setup(c_led, GPIO.OUT)
GPIO.setup(d_led, GPIO.OUT)
GPIO.setup(e_led, GPIO.OUT)
GPIO.setup(f_led, GPIO.OUT)
GPIO.setup(g_led, GPIO.OUT)

try:
	while(True):
		GPIO.output(a_led, False)
		GPIO.output(b_led, False)
		GPIO.output(c_led, False)
		GPIO.output(d_led, False)
		GPIO.output(e_led, False)
		GPIO.output(f_led, False)
		GPIO.output(g_led, True)
		time.sleep(1)

		GPIO.output(a_led, True)
		GPIO.output(b_led, False)
		GPIO.output(c_led, False)
		GPIO.output(d_led, True)
		GPIO.output(e_led, True)
		GPIO.output(f_led, True)
		GPIO.output(g_led, True)
		time.sleep(1)
		GPIO.output(a_led, False)
		GPIO.output(b_led, False)
		GPIO.output(c_led, True)
		GPIO.output(d_led, False)
		GPIO.output(e_led, False)
		GPIO.output(f_led, True)
		GPIO.output(g_led, False)
		time.sleep(1)
		GPIO.output(a_led, False)
		GPIO.output(b_led, False)
		GPIO.output(c_led, False)
		GPIO.output(d_led, False)
		GPIO.output(e_led, True)
		GPIO.output(f_led, True)
		GPIO.output(g_led, False)
		time.sleep(1)

		GPIO.output(a_led, True)
		GPIO.output(b_led, False)
		GPIO.output(c_led, False)
		GPIO.output(d_led, True)
		GPIO.output(e_led, True)
		GPIO.output(f_led, False)
		GPIO.output(g_led, False)
		time.sleep(1)

		GPIO.output(a_led, False)
		GPIO.output(b_led, True)
		GPIO.output(c_led, False)
		GPIO.output(d_led, False)
		GPIO.output(e_led, True)
		GPIO.output(f_led, False)
		GPIO.output(g_led, False)
		time.sleep(1)

		GPIO.output(a_led, False)
		GPIO.output(b_led, True)
		GPIO.output(c_led, False)
		GPIO.output(d_led, False)
		GPIO.output(e_led, False)
		GPIO.output(f_led, False)
		GPIO.output(g_led, False)
		time.sleep(1)
		GPIO.output(a_led, False)
		GPIO.output(b_led, False)
		GPIO.output(c_led, False)
		GPIO.output(d_led, True)
		GPIO.output(e_led, True)
		GPIO.output(f_led, False)
		GPIO.output(g_led, True)
		time.sleep(1)

		GPIO.output(a_led, False)
		GPIO.output(b_led, False)
		GPIO.output(c_led, False)
		GPIO.output(d_led, False)
		GPIO.output(e_led, False)
		GPIO.output(f_led, False)
		GPIO.output(g_led, False)
		time.sleep(1)

		GPIO.output(a_led, False)
		GPIO.output(b_led, False)
		GPIO.output(c_led, False)
		GPIO.output(d_led, False)
		GPIO.output(e_led, True)
		GPIO.output(f_led, False)
		GPIO.output(g_led, False)
		time.sleep(1)

except KeyboardInterrupt:
	GPIO.cleanup()
