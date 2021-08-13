import os
import sys
 
from PyQt5.QtCore import QUrl, pyqtSlot, QObject, pyqtSignal
from PyQt5.QtWebChannel import QWebChannel
from PyQt5.QtWidgets import QMainWindow, QApplication
 
from ui import Ui_MainWindow
 
 
class TInteractObj(QObject):
    """
    一个槽函数供js调用(内部最终将js的调用转化为了信号),
    一个信号供js绑定,
    这个一个交互对象最基本的组成部分.
    """
 
    # 定义信号,该信号会在js中绑定一个js方法.
    sig_send_to_js = pyqtSignal(str)
 
    def __init__(self, parent=None):
        super().__init__(parent)
        # 交互对象接收到js调用后执行的回调函数.
        self.receive_str_from_js_callback = None
 
    # str表示接收str类型的信号,信号是从js发出的.可以出传递的参数类型有很多种：str、int、list、object、float、tuple、dict等等
    @pyqtSlot(str)
    def receive_str_from_js(self, str):
        print('接受消息str is ',str)
        self.receive_str_from_js_callback(str)
 
 
class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
 
        # self.index = (os.path.split(os.path.realpath(__file__))[0]) + "/demo14.html"
        # self.webview.load(QUrl.fromLocalFile(self.index))
        self.webview.load(QUrl("file:/home/embed/ebf_dir/pyqt/hello8/c.html"))
        self.init_channel()
 
    def init_channel(self):
        """
        为webview绑定交互对象
        """
        self.interact_obj = TInteractObj(self)
        self.interact_obj.receive_str_from_js_callback = self.receive_data
 
        channel = QWebChannel(self.webview.page())
        # interact_obj 为交互对象的名字,js中使用.
        channel.registerObject("interact_obj", self.interact_obj)
 
        self.webview.page().setWebChannel(channel)
 
    def receive_data(self, data):
        self.textBrowser.setText(data)
 
    @pyqtSlot()
    def on_pushButton_clicked(self):
        if not self.textBrowser.toPlainText():
            return
        # 这个信号是在js中和一个js方法绑定的,所以发射这个信号时会执行对应的js方法.
        print('pyqt发送消息')
        self.interact_obj.sig_send_to_js.emit(self.textBrowser.toPlainText())
        self.textBrowser.clear()
 
 
if __name__ == '__main__':
    app = QApplication(sys.argv)
    ui = MainWindow()
    ui.show()
    sys.exit(app.exec_())


#########################################
## https://blog.csdn.net/qq_37193537/article/details/90904331?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162886055316780357279334%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162886055316780357279334&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-90904331.first_rank_v2_pc_rank_v29&utm_term=pyqt%E4%B8%8Ehtml%E9%80%9A%E8%AE%AF&spm=1018.2226.3001.4187