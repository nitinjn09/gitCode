class Emps:
    __total = 0  #class properties/ static data member : classname.datamember
    def __init__(self,a,b,c):
        print("I am ready")
        self.name = a
        self.dept = b
        self.sal = c
        Emps.__total = Emps.__total + self.sal

    def show(self):
        print(self.name, self.dept, self.sal)
        
    @staticmethod
    def showTotal():
        print("Total = ",Emps.__total) #access static datamember


