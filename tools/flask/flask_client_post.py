import requests
# url = "http://192.168.1.111:1234"
# url = "http://119.3.7.206:1236"    # for huawei server
# url = "http://124.70.80.182:1234/"    # for yaoqi server
# url = "http://hello654321.tpddns.cn:5006/"    # for local server
url = "http://180.76.190.194:80/"    # for baidu server
data = {"username":"123","password":"123","data":"post test succeed !!!"}
res = requests.post(url=url,data=data)
# print(res.text)
if res.text == '200':
    print('post request SUCCEED')
else :
    print('post request FAIL')
