'''
Created on 19 dec. 2017

@author: Skiry
'''

class Controller:
    '''
    classdocs
    '''


    def __init__(self, drvRepo):
        '''
        Constructor
        '''
        self._drvRepo = drvRepo
        
    def add(self,drv):
        self._drvRepo.add(drv)
        
    def getId(self, id):
        return self._drvRepo.getId(id)