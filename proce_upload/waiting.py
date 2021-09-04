import os
import time

if __name__ == '__main__':
  mtime_before = os.stat('/home/user000/upload/code.txt').st_mtime
  while True:
    time.sleep(0.01)
    mtime_new = os.stat('/home/user000/upload/code.txt').st_mtime
    if(mtime_new != mtime_before):
      print('get the new file')
      f = open('/home/user000/upload/board.txt')
      code_str = f.read()
      #print(code_str)
      if(code_str.find('f103c8')!=-1):
        #print('get f103c8 board')
        os.system('./f103c8.sh')
      elif(code_str.find('f103ze')!=-1):
        #print('get f103ze board')
        os.system('./f103ze.sh')
      else:
        print('cannot find and board paired!')
      time.sleep(0.01)
      print("finished")
      mtime_before = mtime_new
