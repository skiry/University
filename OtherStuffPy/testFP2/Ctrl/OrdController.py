'''
Created on 19 dec. 2017

@author: Skiry
'''
from Classes.Order import *
from Classes.Taxi import *
class OrdersCtrl:
    '''
    classdocs
    '''


    def __init__(self, drvRepo, ordRepo):
        '''
        Constructor
        '''
        self._drvRepo = drvRepo
        self._ordRepo = ordRepo
    
    def add(self,ord):
        id = ord.getId()
        dist = ord.getDist()
        try:
            id = int(id)
            dist = int(dist)
            if id not in self._drvRepo.getAll():
                raise ValueError("Id inexistent")
            if dist < 1:
                raise ValueError("Distance must be at least 1")
        except ValueError as exc:
            raise ValueError(exc)
        self._ordRepo.add(ord)
        
         
    def getSum(self, idS):
        sum = 0
        for i in self._ordRepo.getAll():
            for j in self._ordRepo.getAll()[i]:
                if j.getId() == idS:
                    sum+= j.getDist()*2.5
                
        return sum
    
    def getAll(self):
        return self._ordRepo.getAll()