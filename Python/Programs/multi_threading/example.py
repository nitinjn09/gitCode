from multiprocessing import Process
from threading import Thread
import time
import os

class myProcess(Process):
  def __init__(self):
    Process.__init__(self)
  def run(self):
    print("Hello")
    time.sleep(1)
    
if __name__ == '__main__':
    p1 = myProcess()
    p2 = myProcess()
    p1.start()
    p2.start()
    p1.join()
    p2.join()
