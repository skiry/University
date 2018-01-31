import sys
sys.path.append('./..')
from Controller.Game import *
from Class.Point import *
from Repo.Board import *

class UserInterface:
    def __init__(self,game):
        '''
        initialize the game and call the start function
        '''
        self._game = game
        self._start()

    def _start(self):
        '''
        function which takes care of the user input, and calls other functions from different classes
        '''
        try:
            user = input("Do you want to be the first? (Y/n)")
            if user.lower() != 'y' and user.lower() != 'n': 
                raise ValueError("Please answer with Yes or No.")
            if user.lower() == 'y':
                user = 1 # user is the first
            else:
                user = 0 # computer is the first
            counter = 0
            while counter < 42:
                #until all the positions are taken, go on
                counter += 1
                print("ctr:",counter)
                if user == 1:
                    try:
                        x = int(input("Your column: (1 to 7)"))
                        if x not in range(1,8):
                            raise ValueError("Respect the limits")
                        matrice = self._game._board._matrix
                        for i in range(0,6):
                            if matrice[i][x-1] == 0:
                                self._game.makeMoveUser(Point(i,x-1))
                                i = 10
                                break
                        if i != 10:
                            raise ValueError("This column is full.")
                    except ValueError:
                        raise ValueError
                elif user == 0:
                    print("Computer: ")
                    pcMove = self._game.makeMoveAI()
                    print("hisMove",pcMove)
                    if pcMove == False:
                        counter = 50
                        print("Congratulations !!!!!!!!!")
                    elif pcMove == 7:
                        counter = 50
                        print("Maybe another time!")
                user += 1
                user %= 2
                print(self._game.getBoard())
        except Exception as exc:
            print(exc)
b = Board()
g = Game(b)
u = UserInterface(g)
