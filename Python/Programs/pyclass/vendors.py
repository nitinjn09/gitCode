#Method over-ridding

class vendorA:
  def __init__(self):
   pass
  def fun1(self):
   print("vendora---->fun1")
  def fun2(self):
   print("vendora---->fun2")

class vendorB:
  def __init__(self):
   pass
  def fun1(self):
   print("vendorb+++++>fun1")
  def fun2(self):
   print("vendorb+++++>fun2")

class Alpha(vendorA,vendorB):
  def __init__(self):
   vendorA.__init__(self)
   vendorB.__init__(self)
  def fun1(self):
   super().fun1()
   vendorB.fun1(self)
   print("ALPHA....>fun1")
  def fun2(self):
   print("ALPHA....>fun2")
  def fun3(self):
   print("Alph....Fun3")

class Beta(Alpha):
  def __init__(self):
   Alpha.__init__(self)
  def fun4(self): 
   print("Beta ==== Fun4")

b1 = Beta()
b1.fun1()





