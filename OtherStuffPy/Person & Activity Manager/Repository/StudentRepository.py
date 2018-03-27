'''
Created on 15 nov. 2017

@author: Skiry
'''
import sys
sys.path.append("./..")
from Class.Person import *
'''
import mysql.connector
from mysql.connector import errorcode
'''

class StudentRepository:
    '''
    Holds the student entities
    '''
    def __init__(self):
        """
        Constructor for repository class
        """
        self.__data = {}
        '''
        try:
            self._connection = mysql.connector.connect(user = 'root', database = 'activitiesfp')
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
                print("Something is wrong with your user name or password")
            elif err.errno == errorcode.ER_BAD_DB_ERROR:
                print("Inexistent database!")
            else:
                print(err)
        self._cnx = self._connection.cursor()
        '''
        
    def add(self,person):
        """
        Add an entity to a list
        person - object
        the last line creates an object of type Person
        """
        self.__data[person.getId()] = person
        '''
        query = ("SELECT id FROM `persons`")
        self._cnx.execute(query)
        ok = 1
        for i in self._cnx:
            if person.getId() == i[0]:
                ok = 0
        if ok:
            add = ("INSERT INTO `persons` (`id`, `name`, `number`, `address`) VALUES (%s, %s, %s, %s);")
            self._cnx.execute(add,(person.getId(),person.getName(),person.getNumber(),person.getAddress()))
            # Make sure data is committed to the database
            self._connection.commit()
        '''
        
    def __len__(self):
        """
        Overwriting the len() built-in function
        """
        return len(self.__data)
        
    def get(self,index):
        """
        Get a student from the repository
        index - Index 
        RepositoryException - If an invalid index is given
        """ 
        if index in self.__data:
            return self.__data[index]
        else:
            raise studRepositoryException("Nu exista")
    
    def update(self,person):
        '''
        updates the person with the id introduced by the user with the accordingly data
        '''
        self.__data[person.getId()] = person
        '''
        upd = ("UPDATE `persons` SET `name` = %s, `number` = %s, `address` = %s WHERE `persons`.`id` = %s")
        self._cnx.execute(upd,(person.getName(),person.getNumber(),person.getAddress(),person.getId()))
        # Make sure data is committed to the database
        self._connection.commit()
        '''
        
    def find(self,id):
        '''
        check if a person with ID is in the dictionary
        return : -True if the id exists
                 -False otherwise
        '''
        if id in self.__data:
            return True
        return False
    
    def checkNumber(self,number,id):
        '''
        check if number phone is already taken
        '''
        for key in self.__data:
            if str(self.__data[key].getNumber()) == str(number) and key != id:
                return True
        return False
            
    def remove(self,id):
        '''
        remove the person with the given id
        '''
        del self.__data[id]
        '''
        rmv = ("DELETE FROM `persons` WHERE `persons`.`id` = %s")
        self._cnx.execute(rmv,(id,))
        # Make sure data is committed to the database
        self._connection.commit()
        '''

    def __str__(self,obj):
        """
        String representation of this repository
        """
        txt = ""
        txt += "Person " + obj.getId() + " named " +str(obj.getName()) + " has the phone number " + str(obj.getNumber()) + " and lives on " + str(obj.getAddress())+ '\n'
        return txt 
    
    def getAll(self):
        '''
        return all the dictionary
        '''
        return self.__data
    
    def _closeSQL(self):
        self._cnx.close()
        self._connection.close()
        
class studRepositoryException(Exception):
    """
    Exception class for student repository errors
    """
    def __init__(self, message):
        """
        Constructor for repository exception class
        message - A string representing the exception message
        """
        self.__message = message

    def __str__(self):
        return self.__message
  
