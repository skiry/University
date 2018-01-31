'''
Created on 19 dec. 2017

@author: Skiry
'''

class Driver:
    '''
    classdocs
    '''


    def __init__(self, id, name):
        '''
        Constructor
        '''
        self._id = id
        self._name = name
        
    def getName(self):
        return self._name
    
    def getId(self):
        return self._id
    
    def setName(self, id):
        self._id = id