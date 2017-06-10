aList = [21,434,19,43,65,23,234,54,31,21]
aList = list(map(int,aList))
newList = []
for elem in range(0,len(aList)-1):
    if aList[elem] < 100:
        newList.append(aList[elem])

print("List of numbers less than 100: ",newList)
