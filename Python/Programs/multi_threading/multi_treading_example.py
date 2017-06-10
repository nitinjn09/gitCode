from multiprocessing import Process
import time
import os

def job1():
 print("Job1 = ",os.getpid())
 time.sleep(5)

def job2():
 print("Job2 = ",os.getpid())
 time.sleep(3)

if __name__ == '__main__':  # compulsory for multiprocess
 print("MAin = ",os.getpid())
 p1 = Process(target=job1,args=())
 p2 = Process(target=job2,args=())
 p1.start()
 p2.start()
 start = time.time()
 p1.join()
 p2.join() 
 end   = time.time()
 print("Time taken = ",end-start)
 print("Main Ends here.......")






