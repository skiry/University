'''
Created on 21 nov. 2017

@author: Skiry
'''
from Controller.ActivityController import *
from Repository.ActivityRepository import *
from Class.Activity import *
import unittest
class activityControllerTest(unittest.TestCase):
    """
    asserts for class activity
    """
    
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testAdd(self):
        '''
        Test function for Activity class
        '''
        repo = ActivityRepository()
        undoCtrl = UndoController()
        ctrl = ActivityController(repo,undoCtrl)
        with self.assertRaises(activityRepositoryException):
             ctrl.add(("hey",2,11,24,18,31,"meeting"))
        with self.assertRaises(Exception):
            ctrl.remove("hey")
        with self.assertRaises(Exception):
            ctrl.remove(900) 
        ctrl.add((1,2,11,24,18,31,"meeting"))
        ctrl.add((3,2,11,25,18,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.add((2,2,"test",24,18,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.add((2,2,21,24,18,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.add((2,2,11,24,"test",31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.add((2,2,21,24,28,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.add((1,2,11,24,"test",31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.add((1,2,11,29,18,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.add((1,2,11,24,18,31,"meeting"))
        ctrl.add((1,3,0,0,0,0,0))  
        with self.assertRaises(Exception):
             ctrl.remove("hey")      
        with self.assertRaises(Exception):
             ctrl.remove(9421)
             
        with self.assertRaises(activityRepositoryException):
             ctrl.update(("hey",2,11,24,18,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.update((2,2,"test",24,18,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.update((2,2,21,24,18,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.update((2,2,11,24,"test",31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.update((2,2,21,24,28,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.update((1,2,11,24,"test",31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.update((1,2,11,35,18,31,"meeting"))
        with self.assertRaises(activityRepositoryException):
             ctrl.update((100,2,11,27,18,31,"meeting"))
        self.assertTrue(ctrl.existentActPers(1,2))
        ctrl.update((1,2,11,24,18,31,"meetingssss"))
        ctrl.dateSearch("24")
        with self.assertRaises(Exception):
             ctrl.dateSearch("34")
        ctrl.timeSearch("8:3")
        with self.assertRaises(Exception):
             ctrl.timeSearch("4:8")
        ctrl.descrSearch("eet")
        with self.assertRaises(Exception):
             ctrl.descrSearch("met")
        myAct = Activity(1,2,date(2018,11,24),time(18,31),"mic dejun cu familia")
        myAct.setPersId(2)
        myAct.setDate(date(2017,11,11))
        myAct.setTime(time(5,30))
        myAct.setDescr("pranz")
        myAct.getTime()
        ctrl.getAll()
        print(len(repo),str(repo))
        repo.get(1)
        with self.assertRaises(activityRepositoryException):
            repo.get(203)
        a1 = ctrl.allPersons()
        a1 = ctrl.busiestDays()
        a1 = ctrl.upcomingAct(2)
        a1 = ctrl.dayActivities(date(2018,11,24))
        ctrl.removePers(3)
        repo.remove(1)
        ctrl.remove(3)
             
             
                   