a = [1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]
b = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

intersect = []
union = []
for i in range(0, len(a)):
   if a[i] not in union: 
       union.append(a[i])
   for j in range(0, len(b)):
       if a[i] == b[j]:
           if a[i] not in intersect:
               intersect.append(a[i])
       if b[j] not in union:
            union.append(b[j])

print("a = ",a)
print("b = ",b)
print("Intersect of a and b: ",intersect)
print("Union of a and b: ",union)

