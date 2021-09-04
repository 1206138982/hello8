import os
import time

if __name__ == '__main__':
  os.system('./bef_make.sh')
  time.sleep(0.01)
  os.system('./exchange_code.sh')
  os.system('./making.sh')
  os.system('./aft_make.sh')
  print("finished of making")
