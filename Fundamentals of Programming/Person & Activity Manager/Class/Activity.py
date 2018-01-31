'''
Created on 20 nov. 2017

@author: Skiry
'''
from datetime import date,time
class Activity:
    '''
    Instances of this class represent persons
    '''
    
    def __init__(self,id,pId,date,time,descr):
        """
        Constructor for Activity class
        Input: activity id,person id,date,time and a description for an activity
        """
        self.__id = id 
        self.__pId = pId
        self.__date = date
        self.__time = time
        self.__descr = descr
    
    def getActId(self):
        return self.__id
    
    def getPersId(self):
        return self.__pId
    
    def getDate(self):
        return str(self.__date)        
            
    def getTime(self):
        additionalZero = additionalHour = ''
        if self.__time.minute<10:
            additionalZero = '0'
        if self.__time.hour<10:
            additionalHour = '0'
        return additionalHour + str(self.__time.hour) + ":" + additionalZero + str(self.__time.minute)
    
    def getDay(self):
        return int(self.getDate()[8:10])
    
    def getMonth(self):
        return int(self.getDate()[5:7])
    
    def getHour(self):
        return int(self.getTime()[0:2])
    
    def getMinute(self):
        return int(self.getTime()[3:5])
          
    def getDescr(self):
        return self.__descr
    
    def setPersId(self,pId):
        self.__pId = pId
    
    def setDate(self,date):
        self.__date = date
            
    def setTime(self,time):
        self.__time = time
            
    def setDescr(self,descr):
        self.__descr = descr