
import random
country_list = ["india", "pakistan","china","srilanka","bangladesh","nepal","bhutan"]
country = country_list[random.randint(0,len(country_list)-1)]
country = list(country)
contry_length = len(country)
input_letters = [" - "]*contry_length
failed_guess_counts = 0
choice_count = 0
right_letter_counts = 0
win_flag = False

while True:
    while failed_guess_counts <= contry_length:
        if right_letter_counts == len(input_letters):
            print("Congratulations!! You win.")
            win_flag = True
            break
        print(input_letters)
        choice = str(input("\nGuess the letter: ").lower())
        if len(choice) != 1:
            print("Input should be of one character. Try again..")
            continue
        guess_flag = False
        if choice not in input_letters:
            for i in range(contry_length):
                if choice == country[i]:
                    input_letters[i] = choice
                    right_letter_counts += 1
                    guess_flag = True
        else:
            continue
        if guess_flag == False:
            if failed_guess_counts == (contry_length):
                print("\nYou lose. You have crossed threshold of ",failed_guess_counts+1," wrong guesses\n")
                win_flag = False
                break
            failed_guess_counts += 1
            print("Oops :( Wrong guess. You are left with ",(contry_length - failed_guess_counts)+1,"guesses only")
    if win_flag == False:
        ch = str(input("Do you want to try more guesses for same country (Y/N)?").lower())
        if ch == "y":
            failed_guess_counts = 0
            continue
        elif ch == "n":
            break
        else:
            print("Invalid input. Exiting..")
            break
print("\nThank You for playing Hangman Game\n")
        
                       
            

        
        

