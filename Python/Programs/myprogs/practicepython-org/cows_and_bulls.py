'''Create a program that will play the “cows and bulls” game with the user.
The game works like this:

Randomly generate a 4-digit number. Ask the user to guess a 4-digit number.
For every digit that the user guessed correctly in the correct place, they
have a “cow”. For every digit the user guessed correctly in the wrong place
is a “bull.” Every time the user makes a guess, tell them how many “cows”
and “bulls” they have. Once the user guesses the correct number, the game is
over. Keep track of the number of guesses the user makes throughout teh game
and tell the user at the end.
'''

import random

num_gen = random.randint(1000, 9999)
num_gen = str(num_gen)
print(num_gen)
cows = 0
bulls = 0
guesses = 0

print('''\nGAME: COWS and BULLS
    We have a 4 digit random number and that you have to guess.
    For every digit that you guessed correctly in the correct place, you
    have a “cow”. For every digit you guessed correctly in the wrong place
    is a “bull.” Every time you makes a guess, we will tell how many “cows”
    and “bulls” you have. Once you guesses the correct number, the game is
    over.
    You can enter q/Q anytime to quit the game and see answer\n''')

while True:
    num_user = input("\nEnter a 4-digit number: ")
    if len(num_user) != 4:
        print("Number should be of 4-digit. Try again")
        continue
    if num_user == "q" or num_user == "Q":
        print("Number is: ",num_gen, "Exting..")
        break
    for i in range(0, len(num_gen)):
        for j in range(0, len(num_user)):
            if i == j:
                if num_gen[i] == num_user[j]:
                    cows = cows+1
                elif num_user[j] in num_gen:
                    bulls = bulls+1
    guesses = guesses+1
    if cows == 4:
        print("You win in ",guesses," guesses. Number: ",num_gen)
        break
    else:
        print("Cows: ",cows,"Bulls: ",bulls, ":( [Try again]")
        cows = 0
        bulls = 0

