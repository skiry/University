'''
Created on 10 dec. 2017

@author: Skiry
'''
import sys
sys.path.append("./..")
from Repository.ActivityRepository import ActivityRepository
from Class.Activity import Activity
from _datetime import date,time
class CSVActivities(ActivityRepository):
    '''
    repository for activities with inheritance from the inmemory repo
    '''


    def __init__(self, fileName = "Activities.txt"):
        '''
        Constructor
        '''
        ActivityRepository.__init__(self)
        self.__fileName = fileName
        self.__readFromFile()
        #self.__storeData()
        
    def add(self, activity):
        ActivityRepository.add(self, activity)
        self.__storeData()
        
    def remove(self, id):
        ActivityRepository.remove(self, id)
        self.__storeData()
        
    def update(self, activity):
        ActivityRepository.update(self, activity)
        self.__storeData()
    
    def removePersAct(self, tup):
        ActivityRepository.removePersAct(self, tup)
        self.__storeData()
         
    def __readFromFile(self):
        '''
        function for reading the .txt file
        '''
        f = open(self.__fileName, "r")
        lines = f.read().split('\n')
        for line in lines:
            if line != "":
                elements = line.split(';')
                id = int(elements[0])
                pId = int(elements[1])
                year = int(elements[2])
                month = int(elements[3])
                day = int(elements[4])
                hour = int(elements[5])
                minute = int(elements[6])
                descr = elements[7]
                activity = Activity(id,pId,date(year,month,day),time(hour,minute),descr)
                ActivityRepository.add(self, activity)
        f.close()
       
    def __storeData(self):
        f = open(self.__fileName, "w")
        activities = ActivityRepository.getAll(self)
        for line in activities:
            for el in activities[line]:
                id = el.getPersId()
                month = el.getMonth()
                day = el.getDay()
                hour = el.getHour()
                minute = el.getMinute()
                descr = el.getDescr()
                txt = str(line) + ";" + str(id) + ";2018;" + str(month) + ";" + str(day) + ";" + str(hour) + ";" + str(minute) + ";" + descr + '\n'
                f.write(txt)
        f.close()
            
            