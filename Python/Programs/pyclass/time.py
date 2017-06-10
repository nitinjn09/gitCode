class myTime:
  def __init__(self,hour=0,min=0,sec=0):
    self.h = hour
    self.m  = min
    self.s  = sec

  def show(self):
    print("%d:%d:%d" %(self.h,self.m,self.s))

  def __eq__(self,anoth):
    if self.h==anoth.h and self.m==anoth.m and self.s==anoth.s:
     return True
    else:
     return False

t1 = myTime(10,20,30)
t2 = myTime(10,20,30)
t1.show()
t2.show()
if t1 == t2:    
  print("yes")
else:
  print("no")
