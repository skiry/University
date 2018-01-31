'''
Created on 5 dec. 2017

@author: Skiry
'''
from XO.Point import Point

class UI:
    '''
    The user interface class that reads and prints stuff
    '''


    def __init__(self, game):
        '''
        Constructor
        '''
        self.__game = game
        self.__start()
        
    def __start(self):
        crtPlayer = 3
        while self.__game.getBoard().isGameWon() == False and self.__game.getBoard().avMoves() != []:
            try:
                print(self.__game.getBoard())
                if crtPlayer == 3:
                    x = int(input("coord x: "))
                    y = int(input("coord y: "))
                    point = Point(x,y)
                    try:
                        self.__game.makeMovePlayer(point)
                    except Exception as exc:
                        raise Exception(exc)
                    crtPlayer = 0
                else:
                    print("Computer: ")
                    self.__game.makeMoveAI()
                    crtPlayer = 3
            except Exception as exc:
                print(exc)
        if self.__game.getBoard().isGameWon() == True:
            if crtPlayer == 3:
                print("Computer has won")
            else:
                print("You have won")
        else:
            print("It is a draw")
        print(self.__game.getBoard())