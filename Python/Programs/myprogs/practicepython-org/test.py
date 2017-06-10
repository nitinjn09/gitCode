a  = "Nitin"

if "n" in a:
    print("Yes")
else:
    print("NO")

print(a[3], a[2])
#a = a.replace(a[3],a[2])
a = list(a)
print(a)
a[3] = a[2]
print(a)

'''
try:
    index = a.index("p")
except Exception as ex:
print(index)
    '''
