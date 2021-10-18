download image 相关：
STMFlashLoader.exe使用前提：
安装setup/flash_loader_demo_v2.8.0.exe

pyqt5环境搭建（参考https://blog.csdn.net/yl_best/article/details/83749861?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163403627816780269865397%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163403627816780269865397&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-83749861.first_rank_v2_pc_rank_v29&utm_term=pyqt5%E7%8E%AF%E5%A2%83%E6%90%AD%E5%BB%BA%EF%BC%88python%EF%BC%89&spm=1018.2226.3001.4187）：
pip install PyQt5 -i https://pypi.douban.com/simple
pip install PyQt5-tools -i https://pypi.douban.com/simple
pip install PyQtWebEngine
pip3 install pyinstaller -i http://mirrors.aliyun.com/pypi/simple  --trusted-host mirrors.aliyun.com

pyinstaller -F --distpath . main.py

公网ip相关：
路由器重启后会重新拨号上网，这样公网ip就会变化；
tplink路由器的应用管理中有DDNS，可以申请一个自己的域名，这样即使公网ip有变化，通过申请的域名即可访问到该站点；
然后通过应用管理中的虚拟服务器，配置外部端口为5005，将该端口映射到内部ubuntu的ip，和端口22，即可ssh访问ubuntu；
但是在配置好以上步骤之后，刚开始重启路由器，公网ip还是会变化，但是之后再重启路由器，公网ip却不再发生变化了；再把ddns中的域名退出，重启路由器，公网ip又发生变化了！
