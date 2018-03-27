'''
Created on 19 dec. 2017

@author: Skiry
'''

class Order:
    '''
    classdocs
    '''


    def __init__(self, id, dist):
        '''
        Constructor
        '''
        self._id = id
        self._dist = dist
        
    def getId(self):
        return self._id
    
    def getDist(self):
        return self._dist
    
    def setDist(self, dist):
        self._dist = dist