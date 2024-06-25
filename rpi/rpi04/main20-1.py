# 동일한 폴더 위치에 templates 폴더를 만들고 거기에 html 파일을 저장한다.

from flask import Flask, request, render_template
import RPi.GPIO as GPIO

app = Flask(__name__)

r_led = 19

GPIO.setmode(GPIO.BCM)
GPIO.setup(r_led, GPIO.OUT)

@app.route('/')
def home():
	return render_template("index.html")

@app.route('/data', methods = ['POST'])
def data():
	data = request.form['led']

	if(data == 'on'):
		GPIO.output(r_led, False)
		return home()

	elif(data == 'off'):
		GPIO.output(r_led, True)
		return home()

if __name__ == '__main__':
	app.run(host = '0.0.0.0', port = '80')
