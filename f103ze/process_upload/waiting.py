import os
import time

if __name__ == '__main__':
  mtime_before = os.stat('/home/user000/upload/code.txt').st_mtime
  while True:
    time.sleep(0.01)
    mtime_new = os.stat('/home/user000/upload/code.txt').st_mtime
    if(mtime_new != mtime_before):
      print('get the new file')
      os.system('./bef_make.sh')
      time.sleep(0.01)
      os.system('./exchange_code.sh')
      f = open('/home/user000/upload/board.txt')
      board_str = f.read()
      if(board_str.find('f103c8')!=-1):
        os.system('./c8make.sh')
      elif(board_str.find('f103ze')!=-1):
        os.system('./zemake.sh')
      else:
        print('cannot find board paired!')
      os.system('./aft_make.sh')
      print("finished of making")
      mtime_before = mtime_new
