# URL 접속을/led/on, /led/off로 접속하면 led를 on, off 하는 페이지를 만들자
from flask import Flask

import RPi.GPIO as GPIO

r_led = 19

GPIO.setmode(GPIO.BCM)
GPIO.setup(r_led, GPIO.OUT)

app = Flask(__name__)

# 기본 라우트
@app.route("/")
def hello():
	return "<h1>HELLO<h1>"

# LED 제어 라우트
@app.route("/led/<action>")
def led_control(action):
	if action == "on":
		GPIO.output(r_led, False)
		return "<h1>LED ON<h1>"

	if action == "off":
		GPIO.output(r_led, True)
		return "<h1>LED OFF<h1>"
	
if __name__=="__main__":
	app.run(host="0.0.0.0", port = 10700, debug=True)
