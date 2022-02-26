import os, sys, paramiko, time, my_logging, subprocess

from PyQt5.QtCore import QUrl, pyqtSlot, QObject, pyqtSignal,QFileInfo
from PyQt5.QtWebChannel import QWebChannel
from PyQt5.QtWidgets import QMainWindow, QApplication
 
# from ui import Ui_MainWindow      # for test ui main window  
from ui_new import Ui_MainWindow
import requests
url_server = "http://180.76.190.194:80/"    # for baidu server
data_server = {"username":"123","password":"123","data":"post test succeed !!!"}

# host = "hello654321.tpddns.cn"    # local server
# port = 5005
# host = "119.3.7.206"    # hua wei server
host = "180.76.190.194"    # baidu server
port = 22
username = "user000"
password = "123456"
timeout = 10
fromPath_code = os.path.join(os.getcwd(), "code.txt")
fromPath_board = os.path.join(os.getcwd(), "board.txt")
toPath_code = "/home/user000/upload/code.txt"
toPath_board = "/home/user000/upload/board.txt"

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
        print('pyqt receive code from js:\n',str)
        my_logging.save_log('pyqt receive code from js:\n%s'%(str))
        self.receive_str_from_js_callback(str)
 
class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        my_logging.init_log()
        self.setupUi(self)
 
        # self.webview.load(QUrl("file:/home/embed/ebf_dir/pyqt/hello8/blockly/apps/mixly/index.html"))
        # self.webview.load(QUrl("file://"+QFileInfo("./blockly/apps/mixly/index.html").absoluteFilePath()))    # for ubuntu
        # self.webview.load(QUrl(QFileInfo("./blockly/apps/mixly/index.html").absoluteFilePath()))   # for developing on windows mixly
        # self.webview.load(QUrl(QFileInfo("./gblockly/demos/code/index.html").absoluteFilePath()))   # for developing on windows google
        self.webview.load(QUrl(QFileInfo("./blockly/apps/mixly/index_custom.html").absoluteFilePath()))   # for custom on windows mixly
        self.init_channel()
        self.showMaximized()    #窗口最大化
        self.ready_download = 0

    def init_channel(self):
        # 为webview绑定交互对象
        self.interact_obj = TInteractObj(self)
        self.interact_obj.receive_str_from_js_callback = self.receive_data
 
        channel = QWebChannel(self.webview.page())
        # interact_obj 为交互对象的名字,js中使用.
        channel.registerObject("interact_obj", self.interact_obj)
 
        self.webview.page().setWebChannel(channel)
 
    def receive_data(self, data):
        with open("code.txt","w") as f:
            f.write(data)  # 自带文件关闭功能，不需要再写f.close()
        print('write code to local txt')
        my_logging.save_log('write code to local txt')
        data_server["data"] = data
        res = requests.post(url=url_server,data=data_server)
        # self.upload_code()
        time.sleep(0.1)
        self.get_hex()
 
    @pyqtSlot()
    def on_pushButton_clicked(self):
        # 这个信号是在js中和一个js方法绑定的,所以发射这个信号时会执行对应的js方法.
        self.interact_obj.sig_send_to_js.emit('compile')
        print('pyqt send command to js to get code')
        my_logging.save_log('pyqt send command to js to get code')

    @pyqtSlot()
    # def on_pushButton_2_clicked(self):
    #     self.get_hex()

    def upload_code(self):
        client = paramiko.SSHClient()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect(hostname=host, port=port, username=username, password=password, timeout=timeout)

        sftp_client = paramiko.SFTPClient.from_transport(client.get_transport())
        sftp_client.put(fromPath_code, toPath_code)
        sftp_client.put(fromPath_board, toPath_board)
        sftp_client.close()
        client.close()
        print('send code to server')
        my_logging.save_log('send code to server')

    def get_hex(self):
        print("try to get hex file from server")
        my_logging.save_log("try to get hex file from server")
        getfromPath = "/home/user000/upload/make103.hex"
        gettoPath = os.path.join(os.getcwd(), "Flash_Loader_Demo\make103.hex")
        client = paramiko.SSHClient()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect(hostname=host, port=port, username=username, password=password, timeout=timeout)
        sftp_client = paramiko.SFTPClient.from_transport(client.get_transport())
        sftp_client.get(getfromPath,gettoPath)
        sftp_client.close()
        client.close()
        print("get hex file from server")
        my_logging.save_log("get hex file from server")
        self.downloadingbat()

    def downloadingbat(self):
        print('start to download hex file')
        ret = os.system('start .\download.bat')
        print(ret)
        print('FINISH DOWNLOAD')
        my_logging.save_log('FINISH DOWNLOAD')
        # self.interact_obj.sig_send_to_js.emit('download_success')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ui = MainWindow()
    ui.show()
    sys.exit(app.exec_())
