'''
Created on 5 dec. 2017

@author: Skiry
'''

class Point:
    '''
    Point represented by 2 coordinates
    '''


    def __init__(self, x, y):
        '''
        Constructor
        '''
        self._x = x
        self._y = y
        
    def getX(self):
        return self._x
    
    def getY(self):
        return self._y
    