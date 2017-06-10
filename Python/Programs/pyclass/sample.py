import mylib

mylib.Emps.showTotal()

e1 = mylib.Emps("Arun", "Sales", 15000)
e2 = mylib.Emps("John", "Accts", 18000)
e3 = mylib.Emps("Nitin", "Accts", 21000)
e4 = mylib.Emps("Rahul", "Accts", 23000)

mylib.Emps.showTotal()
e1.show()
e2.show()
e3.show()
e4.show()

print(e1)   #print object
print(e1.__dict__)
print(type(e1))  #mylib.Emps

print(mylib.Emps.__mro__)  #method resolution order. It will say if it is direct class or object class

