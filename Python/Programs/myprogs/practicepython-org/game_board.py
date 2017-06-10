'''
Solution: http://www.practicepython.org/solution/2015/11/23/26-check-tic-tac-toe-solutions.html
input = [[1,2,1],
         [2,1,2],
         [1,2,1]]

win = 

'''
def print_horiz_line():
    print(" ---- " * board_size)

def print_vert_line():
    print("|    |" * board_size)


def print_board():
    for index in range(board_size):
        print_horiz_line()
        print_vert_line()
        print_horiz_line()

def line_match(game):
    if game[0][0] 

def win_lose():


if __name__ == "__main__":
    board_size = int(input("What size of game board? "))




