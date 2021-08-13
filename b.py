import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QObject, pyqtSlot, QUrl
from PyQt5.QtWebChannel import QWebChannel
from PyQt5.QtWebEngineWidgets import QWebEngineView
 
 
class CallHandler(QObject):
    @pyqtSlot(result=str)
    def myHello(self):
        view.page().runJavaScript('uptext("hello, Pythongjhkkkk");')
        print('call received')
        return 'hello, Python'
 
 
    @pyqtSlot(str, result=str)
    def myTest(self, test):
        print('test is',test)
        return '返回前端结果'
 
 
if __name__ == '__main__':
    app = QApplication(sys.argv)
    view = QWebEngineView()
    channel = QWebChannel()
    handler = CallHandler()
    channel.registerObject('pyjs', handler)##前者是str，后者是一个QObject（里面放着需要调用的函数）
    view.page().setWebChannel(channel)
    # url_string = "file:///D:/TY_75Stability/mxh_work/pyqt_work/demo15.html"
    url_string = "file:/home/embed/ebf_dir/pyqt/commu/a.html"
    view.load(QUrl(url_string))
    view.show()
    sys.exit(app.exec_())