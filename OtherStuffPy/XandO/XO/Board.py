'''
Created on 5 dec. 2017

@author: Skiry
'''
from XO.Point import *
from builtins import sum
class Board:
    '''
    The X and O board
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.__board = [ [-1, -1, -1], [-1, -1, -1], [-1, -1, -1] ]
        
    def makeMove(self,point,user):
        u = 0
        if user == "player":
            u = 1
        else:
            u = 0
        
        if point.getX() in range(0,3) and point.getY() in range(0,3):
            if self.__board[point.getX()][point.getY()] == -1:
                if u == 1:
                    self.__board[point.getX()][point.getY()] = 3
                else:
                    self.__board[point.getX()][point.getY()] = 0
            else:
                raise Exception("The square is already taken")
        else:
            raise Exception("Point out of board")
        
    def isGameWon(self):
        for line in self.__board:
            if sum(line) in [0,9]:
                return True
        for line in range(0,3):
            sum1 = 0
            for column in range(0,3):
                sum1 += self.__board[column][line]
            if sum1 in [0,9]:
                return True
        sum1 = sum2 = 0
        for i in range(0,3):
            sum1 += self.__board[i][i]
            sum2 += self.__board[2-i][i]
        if sum1 in [0,9] or sum2 in [0,9]:
            return True
        return False
    
    def avMoves(self):
        moves = []
        for line in range(0,3):
            for column in range(0,3):
                if self.__board[line][column] == -1:
                    moves.append(Point(line,column))
        return moves
    
    def isDraw(self):
        if self.avMoves() == []:
            return True
        return False
    
    def intToStr(self,number):
        if number == -1:
            return " "
        elif number == 0:
            return "O"
        return "X"
    
    def __str__(self):
        result = ""
        lineNumber = 0
        for line in self.__board:
            result += self.intToStr(line[0]) + "|" + self.intToStr(line[1]) + "|" + self.intToStr(line[2]) + '\n'
            if lineNumber in [0,1]:
                result += ("-----\n")
            lineNumber += 1
        return result
'''  
GameBoard = Board()
GameBoard.makeMove(Point(0,0), "user")
GameBoard.makeMove(Point(1,2), "player")
print(GameBoard)                                                                                        
Gm = Game(GameBoard)                                                                                                  
Gm.makeMoveAI()
Gm.makeMoveAI()
Gm.makeMoveAI()
print(Gm._board)
'''        
    
    