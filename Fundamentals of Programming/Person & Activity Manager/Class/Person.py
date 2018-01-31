'''
Created on 7 nov. 2017

@author: Skiry

Person: <personID>, <name>, <phone number>, <address>
Activity: <activityID>, <personIDs>, <date>, <time>, <description>

'''

class Person:
    '''
    Instances of this class represent persons
    '''
    
    def __init__(self,id,name,number,address):
        """
        Constructor for Person class
        Input: id,name,number,address of one person
        """
        self.__id = id
        self.__name = name
        self.__number = number
        self.__address = address
        
    def getId(self):
        return self.__id
    
    def getName(self):
        return self.__name
    
    def getNumber(self):
        return self.__number
    
    def getAddress(self):
        return self.__address
    
    def setName(self,name):
        self.__name = name
    
    def setNumber(self,number):
        self.__number = number
    
    def setAddress(self,address):
        self._address = address
    
