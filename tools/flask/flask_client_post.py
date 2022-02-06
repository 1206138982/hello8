import requests
# url = "http://192.168.1.111:1234"
# url = "http://119.3.7.206:1236"
# url = "http://124.70.80.182:1234/"
url = "http://hello654321.tpddns.cn:5006/"
data = {"username":"123","password":"123","data":"post test succeed !!!"}
res = requests.post(url=url,data=data)
# print(res.text)
