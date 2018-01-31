'''
Created on 19 dec. 2017

@author: Skiry
'''
from Classes.Taxi import *
class DrvRepo:
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.__data = {}
        
    def add(self,driver):
        '''
        add a driver to the list of drivers
        '''
        self.__data[driver.getId()] = driver
        
    def getId(self, id):
        '''
        get the name from the driver indexed with the given id
        '''
        return self.__data[id].getName()
    
    def getAll(self):
        '''
        returns all the drivers
        '''
        return self.__data