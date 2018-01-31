'''
Created on 5 dec. 2017

@author: Skiry
'''
from random import randint
from XO.Board import *
class Game:
    '''
    The game moves
    '''


    def __init__(self, board):
        '''
        Constructor
        '''
        self._board = board
        
    def makeMoveAI(self):
        availableMoves = self._board.avMoves()
        randMove = randint(0,len(availableMoves))
        self._board.makeMove(availableMoves[randMove], "Computer")
        
    def makeMovePlayer(self,point):
        self._board.makeMove(point, "player")
    
    def getBoard(self):
        return self._board