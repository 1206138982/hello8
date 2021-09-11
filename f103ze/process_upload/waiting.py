import os
import time
import logging

logger = ''

def log_init():
  global logger
  # logging.basicConfig(filename='logs.log', filemode='w',format='%(levelname)s -> %(asctime)s: %(message)s', level=logging.DEBUG)
  logging.basicConfig(filename='logs.log', filemode='a',format='%(levelname)s -> %(asctime)s: %(message)s', level=logging.INFO)
  logger = logging.getLogger(__name__)
  save_log('init log success')

def save_log(str):
  logger.info(str)

if __name__ == '__main__':
  mtime_before = os.stat('/home/user000/upload/code.txt').st_mtime
  log_init()
  while True:
    time.sleep(0.01)
    mtime_new = os.stat('/home/user000/upload/code.txt').st_mtime
    if(mtime_new != mtime_before):
      print('get the new file')
      save_log('get new file')
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
      save_log('finished of making')
      mtime_before = mtime_new

