from PyQt5.QtWidgets import *
from PyQt5 import uic
import sys

form_class = uic.loadUiType("./btn01.ui")[0]

class WindowClass(QMainWindow, form_class):
	def __init__(self):
		super().__init__()
		self.setupUi(self)

	#이벤트 함수 등록
		self.btn_1.clicked.connect(self.btn1Function)
		self.btn_2.clicked.connect(self.btn2Function)

	def btn1Function(self):
		print("LED ON Button Clicekd")
	def btn2Function(self):
		print("LED OFF Button Clicked")
	def slot1(self):
		print("EXIT!!")

if __name__ == "__main__":
	app = QApplication(sys.argv)
	myWindow = WindowClass()
	myWindow.show()
	app.exec_()
