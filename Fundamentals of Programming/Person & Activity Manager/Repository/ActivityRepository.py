'''
Created on 20 nov. 2017

@author: Skiry
'''
from Class.Activity import *
from datetime import date,time
import mysql.connector
from mysql.connector import errorcode

class ActivityRepository:
    '''
    Holds the activity entities
    '''
    def __init__(self):
        """
        Constructor for repository class
        """
        self.__data = {}
        try:
            self._connection = mysql.connector.connect(user = 'root', database = 'activitiesfp')
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
                print("Something is wrong with your user name or password")
            elif err.errno == errorcode.ER_BAD_DB_ERROR:
                print("Inexistent database!")
            else:
                print(err)
        self._cnx = self._connection.cursor(buffered=True)
        
    def _closeSQL(self):
        self._cnx.close()
        self._connection.close()
        
    def add(self,activity):
        """
        Add an entity to a list
        typeOf - list
        the last line creates an object of type Activity
        """
        ok = 1
        for i in self.getAll():
            if str(i) == str(activity.getActId()):
                self.__data[activity.getActId()].append(activity)
                ok = 0
        if ok:
            self.__data[activity.getActId()] = [activity]
            
        query = ("SELECT id,pId FROM `activities`")
        self._cnx.execute(query)
        ok = 1
        for i in self._cnx:
            if activity.getActId() == i[0] and activity.getPersId() == i[1]:
                ok = 0
        if ok:
            add = ("INSERT INTO `activities` (`id`, `pId`, `year`, `month`, `day`, `hour`, `minute`, `descr`) VALUES (%s, %s, %s, %s, %s, %s, %s, %s);")
            month = activity.getMonth()
            day = activity.getDay()
            hour = activity.getHour()
            minute = activity.getMinute()
            descr = activity.getDescr()
            id = activity.getActId()
            pId = activity.getPersId()
            self._cnx.execute(add,(id,pId,2018,month,day,hour,minute,descr))
            # Make sure data is committed to the database
            self._connection.commit()
        
    def __len__(self):
        """
        Overwriting the len() built-in function
        """
        return len(self.__data)
        
    def get(self,index):
        """
        Get an acivity from the repository
        index - Index 
        RepositoryException - If an invalid index is given
        """ 
        if index in self.__data:
            return self.__data[index]
        else:
            raise activityRepositoryException("Nu exista")
    
    def removePersAct(self,tup):
        """
        remove a person from an activity
        """
         # if we want to delete duplicates from sql, we don t delete it from txt files bc they don t exist
        activity = tup[0]
        person = tup[1]
        activitate = self.getAll()[activity]
        ok=0
        for j in activitate:
            if j.getPersId() == person:
                del activitate[ok]
            ok += 1
        rmv = ("DELETE FROM `activities` WHERE `activities`.`id` = %s and `activities`.`pId` = %s")
        self._cnx.execute(rmv,(int(activity),int(person)))
        # Make sure data is committed to the database
        self._connection.commit()
        
    def update(self,activity):
        '''
        updates the activity with the id introduced by the user with the accordingly data
        '''
        self.__data[activity.getActId()] = [activity]
        rmv = ("DELETE FROM `activities` WHERE `activities`.`id` = %s")
        self._cnx.execute(rmv,(activity.getActId(),))
        # Make sure data is committed to the database
        self._connection.commit()
        
        add = ("INSERT INTO `activities` (`id`, `pId`, `year`, `month`, `day`, `hour`, `minute`, `descr`) VALUES (%s, %s, %s, %s, %s, %s, %s, %s);")
        month = activity.getMonth()
        day = activity.getDay()
        hour = activity.getHour()
        minute = activity.getMinute()
        descr = activity.getDescr()
        id = activity.getActId()
        pId = activity.getPersId()
        self._cnx.execute(add,(id,pId,2018,month,day,hour,minute,descr))
        # Make sure data is committed to the database
        self._connection.commit()
 
    def find(self,id):
        '''
        check if an activity with ID is in the dictionary
        return : -True if the id exists
                 -False otherwise
        '''
        if id in self.__data:
            return True
        return False
    
    def checkDate(self,date,id=0):
        '''
        check if date and time are the same->overlapping
        '''
        for key in self.__data:
            for i in range(0,len(self.__data[key])):
                if self.__data[key][i].getDate() == str(date) and key != id:
                    return True
        return False
    
    def checkTime(self,time,id=0):
        '''
        check if date and time are the same->overlapping
        '''
        for key in self.__data:
            for i in range(0,len(self.__data[key])):
                if str(self.__data[key][i].getTime()+":00") == str(time) and key != id:
                    return True
        return False
    
    def remove(self,id):
        '''
        remove the activity with the given id
        '''
        del self.__data[int(id)]
        rmv = ("DELETE FROM `activities` WHERE `activities`.`id` = %s")
        self._cnx.execute(rmv,(id,))
        # Make sure data is committed to the database
        self._connection.commit()
        
    def getAll(self):
        '''
        return all the dictionary
        '''
        return self.__data
    
class activityRepositoryException(Exception):
    """
    Exception class for activity repository errors
    """
    def __init__(self, message):
        """
        Constructor for repository exception class
        message - A string representing the exception message
        """
        self.__message = message

    def __str__(self):
        return self.__message
    