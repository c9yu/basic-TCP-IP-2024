#Ultra
import RPi.GPIO as GPIO
import time

piezoPin = 13
melody = [130, 165, 196, 262]
trigPin = 27
echoPin = 17

def measure():
	GPIO.output(trigPin, True)
	time.sleep(0.00001)
	GPIO.output(trigPin, False)
	start = time.time()

	while GPIO.input(echoPin) == False:
		stop = time.time()
	while GPIO.input(echoPin) == True:
		stop = time.time()
	elapsed = stop - start
	distance = (elapsed * 19000)/2

	return distance

GPIO.setmode(GPIO.BCM)
GPIO.setup(piezoPin, GPIO.OUT)
Buzz = GPIO.PWM(piezoPin, 440)

GPIO.setup(trigPin, GPIO.OUT)
GPIO.setup(echoPin, GPIO.IN)

try:
	while True:
		distance = measure()
		print("Distance: %.2fcm" %distance)
		time.sleep(0.1)
		
#		if float(distance) <= 20.99 and float(distance)>= 15:
#			Buzz.start(10)
#			Buzz.ChangeFrequency(melody[0])
#			time.sleep(1.2)
#			Buzz.stop()

		if float(distance) <= 14.99 and float(distance) >= 10:
			Buzz.start(10)
			Buzz.ChangeFrequency(melody[1])
			time.sleep(0.8)
			Buzz.stop()

		elif float(distance)<= 9.99 and float(distance) >= 5:
			Buzz.start(10)
			Buzz.ChangeFrequency(melody[2])
			time.sleep(0.4)
			Buzz.stop()

		elif float(distance) <= 4.99 and float(distance) >= 0:
			Buzz.start(10)
			Buzz.ChangeFrequency(melody[3])
			time.sleep(0.1)
			Buzz.stop()

		else :
			Buzz.stop()
			print("SAFE!")
			time.sleep(1)

except KeyboardInterrupt:
	GPIO.cleanup()
