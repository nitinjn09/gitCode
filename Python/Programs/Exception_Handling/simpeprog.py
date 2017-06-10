import traceback
class ZeroError(Exception):
  def __init__(self,mesg):
   Exception.__init__(self,mesg)
    
try:
   print("Very important start")
   n1 = input("Enter the value of n1 : ")
   n2 = input("Enter the value of n2 : ")
   n1 = int(n1)
   n2 = int(n2)
   if n1==0 or n2==0:
     raise ZeroError("Why did u gave ZEROOOOO....")
   res = n1 + n2
   print("Result = ",res)

except ValueError as e1:
   print("Action-1")
   print(e1)

except EOFError as e2:
   print("Action-2")

except Exception as ex:             # Generic Catch block
   traceback.print_exc()
   print("DEFAULT Action......")
   print(type(ex),ex)
 
finally:
   print("Very very import end")
