#!/usr/bin/python
'''
Created on 21 nov. 2017

@author: Skiry
'''
from Controller.StudentController import *
from Repository.StudentRepository import *
from Class.Person import *
import unittest
class personControllerTest(unittest.TestCase):
    """
    asserts for class person
    """
    
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testAdd(self):
        '''
        Test function for Person class
        '''
        undoCtrl = UndoController()
        repo = StudentRepository()
        ctrl = StudentController(repo,undoCtrl)
        with self.assertRaises(studRepositoryException):
             ctrl.add(("id","John","0755241524","Iulius Street"))
        with self.assertRaises(Exception):
            ctrl.remove("hey")
        with self.assertRaises(Exception):
            ctrl.remove(900) 
        ctrl.add((1,"John","0755241524","Iulius Street")) 
        with self.assertRaises(studRepositoryException):
             ctrl.add((1,"John","0755241524","Iulius Street")) 
        with self.assertRaises(studRepositoryException):
             ctrl.add((200,"John","0755241524","Iulius Street"))  
        with self.assertRaises(studRepositoryException):
             ctrl.add((201,"John","07255241524","Iulius Street")) 
        with self.assertRaises(studRepositoryException):
             ctrl.add((202,"John","2755241524","Iulius Street")) 
        with self.assertRaises(studRepositoryException):
             ctrl.add((203,"John","05524s1524","Iulius Street"))
        with self.assertRaises(Exception):
             ctrl.remove("hey")      
        with self.assertRaises(Exception):
             ctrl.remove(9421)
        ctrl.update((1,"John","0755241524","Polus Street")) 
        with self.assertRaises(studRepositoryException):
             ctrl.update((9124,"John","0755241524","Polus Street"))
        with self.assertRaises(studRepositoryException):
             ctrl.add((1,"John","0755241524","Polus Street"))
        with self.assertRaises(Exception):
             ctrl.update((1,"John","07255241524","Iulius Street")) 
        with self.assertRaises(Exception):
             ctrl.update((1,"John","2755241524","Iulius Street")) 
        with self.assertRaises(Exception):
             ctrl.update((1,"John","05524s1524","Iulius Street"))
        with self.assertRaises(Exception):
             ctrl.update(("hey","John","05524s1524","Iulius Street"))
        ctrl.update((1,"John","0552401524","Iulius Street"))
        self.assertTrue(ctrl.checkPerson(1))
        with self.assertRaises(Exception):
             ctrl.checkPerson(904214)
        ctrl.nameSearch("John")
        with self.assertRaises(Exception):
             ctrl.nameSearch("Johny")
        with self.assertRaises(Exception):
             ctrl.noSearch("5521")
        myPers = Person(2,"Ionut","0724917899","Unknown")
        myPers.setName("Ionutz")
        myPers.setNumber("0766119902")
        myPers.setAddress("Unknown street")
        ctrl.noSearch("552")    
        ctrl.getAll()
        print(len(repo),str(repo))
        repo.add(Person(202,"John","2755241524","Iulius Street")) 
        repo.get(202)
        with self.assertRaises(studRepositoryException):
            repo.get(203)
        repo.remove(202)
        ctrl.remove(1)
             
             
                   
