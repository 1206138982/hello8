from flask import Flask,request
app = Flask(__name__)

@app.route("/",methods=['POST'])
def hello_world():
    if request.form['username']=='123' and request.form['password']=='123':
        print(request.form['data'])
        return "200"
    else:
        print('indvel_user')
        return '300'

if __name__=="__main__":
    app.run(host='0.0.0.0',port=80,debug=True)

