'''
#use of pass statment
for i in range(1,10):
    if i == 5:
        pass
        print "I am in the pass"
    print i
'''
'''
#printing string in reverse order
myName  = "Rupali Jain"
length = len(myName);
print "Length of name: ", length
for i in range(length):
    print myName[i], "\t", myName[-i-1]
'''
'''
def sum(x,y=50):
    "this is to add two numbers"
    s = x+y
    print "sum of ", x ,"and ", y, " is : ", s
    return s
sum(10,20);
sum(40)
'''

sum = lambda x1, x2: x1+x2
s = sum(10,20)
print "sum is : ", s
