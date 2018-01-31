import sys
sys.path.append('./..')
from Repo.Board import *
from Class.Point import *
from random import randint

class Game:
    def __init__(self,board):
        self._board = board

    def makeMoveUser(self,point):
        self._board.addPoint(point, 1)

    def makeMoveAI(self):
        moves = self._board.avMoves()
        done = 0
        if 7 in moves:
            return False # user won. bye
        for x in moves:
            if x != 7 and done == 0:
                for y in moves[x]:
                    belowPoint = Point(y.getX() - 1, y.getY())
                    if self._board.okPoint(belowPoint) == True and self._board.okPoint(y) == False and done == 0:
                        self._board.addPoint(y)
                        done = 1
        if 1 in moves:
            return 7 # AI won. bye too
        return True

    def getBoard(self):
        return self._board
