'''
Created on 19 dec. 2017

@author: Skiry
'''
from Classes.Order import *
class OrdRepo:
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.__data = {}
        
    def add(self, ord):
        '''
        add a order to a driver the list of drivers
        keep a dictionary with a list
        '''
        if ord.getId() in self.__data:
            self.__data[ord.getId()].append(ord)
        else:
            self.__data[ord.getId()] = [(ord)]
  
        
    def getAll(self):
        '''
        get all the orders
        '''
        return self.__data
    