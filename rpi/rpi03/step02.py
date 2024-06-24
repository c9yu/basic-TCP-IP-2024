import RPi.GPIO as GPIO
import time

steps = [21, 22, 23, 24]
GPIO.setmode(GPIO.BCM)

for stepPin in steps:
	GPIO.setup(stepPin, GPIO.OUT)
	GPIO.output(stepPin, 0)

ranges = [[0,0,0,1], [0,0,1,0], [0,1,0,0], [1,0,0,0]]

try:
	while 1:
		for stepPin in range(0, 4):
			#for i in range(0, len(ranges)):
			#GPIO.OUT(steps[i])
			#time.sleep(0.01)
			moter = steps[stepPin]

except KeyboardInterrupt:
	GPIO.cleanup()
