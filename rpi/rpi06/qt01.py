import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic

from_class = uic.loadUiType("./untitled.ui")[0]

class WindowClass(QMainWindow, from_class):
	def __init__(self): # 생성자, 첫번째 인자는 self
		super().__init__() # 부모클래스 생성자(QWidges)
		self.setupUi(self)

if __name__ == "__main__":
	app = QApplication(sys.argv)
	myWindow = WindowClass()
	myWindow.show()
	app.exec_()
