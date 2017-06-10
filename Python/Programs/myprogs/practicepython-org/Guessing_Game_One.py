import random

num = random.randint(1,9)

unum = int(input("Enter your guess between 1 to 9: "))
print("Random number generated: ",num)

if num == unum:
    print("your guess is right")
elif unum < num:
    print("Your guess is low")
else:
    print("Your guesss is high")
