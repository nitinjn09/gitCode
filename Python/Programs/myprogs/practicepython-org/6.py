
string = list(input("Enter a string: "))
for i in range(0,len(string)):
    print(string[i])

reverse  = string[::-1]
if string == reverse:
    print("Sting entered is palindrom")
else:
    print("Sting entered is not a palindrom")

