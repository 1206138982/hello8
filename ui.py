from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5 import QtCore, QtGui, QtWidgets
 
 
class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 570)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.textBrowser = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser.setObjectName("textBrowser")
        self.textBrowser.setReadOnly(False)
        self.gridLayout.addWidget(self.textBrowser, 0, 0, 1, 1)
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setObjectName("pushButton")
        self.gridLayout.addWidget(self.pushButton, 1, 0, 1, 1)
        self.webview = QWebEngineView(self.centralwidget)
        self.webview.setObjectName("webview")
        # self.webview.setMinimumWidth(400)
        self.webview.setMinimumWidth(1600)
        self.gridLayout.addWidget(self.webview, 0, 1, 2, 1)
        MainWindow.setCentralWidget(self.centralwidget)
 
        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)
 
    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pushButton.setText(_translate("MainWindow", "同步到web"))