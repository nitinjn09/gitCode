class Player:
  def __init__(self,name,dob):
    self.name = name
    self.dob  = dob
  def showPlayer(self): 
    print("NAme = ",self.name)
    print("DOB  = ",self.dob)

class Batsman(Player):
  def __init__(self,name,dob,cent):
    Player.__init__(self,name,dob)     # ctor chaining
    self.cent = cent
    self.role = str(type(self)).split(".")[1][:-2]
  def showBatsman(self):
    print("cent = ",self.cent)
    print("Role = ",self.role)

b1 = Batsman("Rahul Dravid","1-1-1970",145)
b1.showPlayer()
b1.showBatsman()

b2 = Batsman("Sourabh Ganguli", "1-2-1970",150)
b2.showPlayer()
b2.showBatsman()

