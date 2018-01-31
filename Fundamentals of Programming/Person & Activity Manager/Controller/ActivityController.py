'''
Created on 20 nov. 2017

@author: Skiry
'''

from Repository.ActivityRepository import *
from datetime import date,time
from Class.Activity import *
from _collections import OrderedDict
from audioop import reverse
from Controller.UndoController import *
from Repository.StudentRepository import *

class ActivityController:
    '''
    The functions that will work with the activityRepository
    We have the functions which will add,remove,update an activity
         and print the list of activities
    '''
    def __init__(self,repo,UndoController,repoSt):
        """
        Constructor for controller class
        We also have the undo list created here.
        """
        self.__repo = repo
        self.__undoController = UndoController
        self.__repoSt = repoSt
    
    def closeSQL(self):
        self.__repo._closeSQL()
        
    def add(self,typeOf):
        """
        Add an entity to a list
        typeOf - object of type activity
        
        check if id is unique
        check if person id is existent
        """
                
        id = typeOf[0]
        pId = typeOf[1] 
        # we have the verification below because from where we read, we can get only id and person id as input,
        # because they will be automatically added in the id activity, 
        # and we do not have month,day,etc, so our program  will not crash
        
        try:
            id = int(id)
            pId = int(pId)
        except Exception:
            raise activityRepositoryException("Integer id")
        
        if self.existentActPers(id,pId):
            raise activityRepositoryException("This id is already registered in this activity")
        
        if self.existentAct(id):
            x = self.__repo.getAll()
            for i in x:
                if str(i) == str(id):
                    month = x[i][0].getMonth()
                    day = x[i][0].getDay()
                    data = date(2018,month,day)
                    hour = x[i][0].getHour()
                    minute = x[i][0].getMinute()
                    obiect = Activity(id,pId,data,time(hour,minute),str(x[i][0].getDescr()))
                    self.__repo.add(obiect)
                    redo = FunctionCall(self.__repo.add,obiect)
                    tup = (id,pId)
                    undo = FunctionCall(self.__repo.removePersAct,tup)
                    op = Operation(redo,undo)
                    self.__undoController.recordOperation(op) 
                    return
        
        month = typeOf[2]
        day = typeOf[3]
        hour = typeOf[4]
        mins = typeOf[5]
        descr = typeOf[6]
    
                    
        try:
            month = int(month)
            day = int(day)
            data = date(2018,month,day)
        except Exception:
            raise activityRepositoryException("Invalid date")
        try:
            hour = int(hour)
            mins = int(mins)
            timp = time(hour,mins)
        except Exception:
            raise activityRepositoryException("Invalid time")
        
        if self.__repo.checkDate(data) and self.__repo.checkTime(timp):
            raise activityRepositoryException("The activities must not overlap")        
        else:
            self.__repo.add(Activity(id,pId,data,timp,descr))
            redo = FunctionCall(self.__repo.add,Activity(id,pId,data,timp,descr))
            undo = FunctionCall(self.__repo.remove,id)
            op = Operation(redo,undo)
            self.__undoController.recordOperation(op)
    
    def remove(self,id,makeUndo = False):
        """
        Remove an entity from the list
        id - identifier
        
        check if id exists
        """
        try:
            id = int(id)
            cascade = CascadedOperations()
            if self.__repo.find(id):
                redo = FunctionCall(self.__repo.remove,id)
                x = self.__repo.getAll()[id]
                for j in x:
                    month = j.getMonth()
                    day = j.getDay()
                    data = date(2018,month,day)
                    hour = j.getHour()
                    minute = j.getMinute()
                    obiect = Activity(id,j.getPersId(),data,time(hour,minute),str(j.getDescr()))
                    if makeUndo:
                        undo = FunctionCall(self.__repo.add,obiect)
                        op = Operation(redo,undo)
                        cascade.add(op)
                self.__repo.remove(id)
            else:
                raise Exception
            if makeUndo:
                self.__undoController.recordOperation(cascade)
        except Exception:
            raise activityRepositoryException("Id not found")
        
    def update(self,typeOf):
        """
        Update an entity from the list
        typeOf - object of type activity
        
        check if id exists
        check if new student id is ok
        """
        id = typeOf[0]
        pId = typeOf[1]
        month = typeOf[2]
        day = typeOf[3]
        hour = typeOf[4]
        mins = typeOf[5]
        descr = typeOf[6]
        try:
            id = int(id)
            pId = int(pId)
        except Exception:
            raise activityRepositoryException("Integer id")
        
        try:
            month = int(month)
            day = int(day)
            data = date(2018,month,day)
        except Exception:
            raise activityRepositoryException("Invalid date")
        try:
            hour = int(hour)
            mins = int(mins)
            timp = time(hour,mins)
        except Exception:
            raise activityRepositoryException("Invalid time")
        if self.__repo.checkDate(data,id) and self.__repo.checkTime(timp,id):
            raise activityRepositoryException("The activities must not overlap")
        if self.__repo.find(id) == False:
            raise activityRepositoryException("This id is inexistent")
        redo = FunctionCall(self.__repo.update,Activity(id,pId,data,timp,descr))
        cascaded = CascadedOperations()
        for j in self.__repo.getAll()[id]:
            month = j.getMonth()
            day = j.getDay()
            data = date(2018,month,day)
            hour = j.getHour()
            minute = j.getMinute()
            obiect = Activity(id,j.getPersId(),data,time(hour,minute),str(j.getDescr()))
            undo = FunctionCall(self.__repo.update,obiect)
            op = Operation(redo,undo)
            cascaded.add(op)
        self.__undoController.recordOperation(cascaded)
        self.__repo.update(Activity(id,pId,data,timp,descr))
        
    def dateSearch(self,data):
        '''
        input : date
        return : any date that contains the input date
        '''
        ok = 1;
        try:
            for key in self.__repo.getAll():
                for i in range(0,len(self.__repo.getAll()[key])):
                    if (self.__repo.getAll()[key][i].getDate().find(data)) >=0:
                        print(self.__repo.getAll()[key][i].getDate(),": ",self.__repo.getAll()[key][i].getDescr())
                        ok = 0
            if ok:
                raise Exception
        except Exception:
            raise Exception("No date found")
        
    def timeSearch(self,timp):
        '''
        input : time
        return : any time that contains the input time
        '''
        ok = 1;
        try:
            for key in self.__repo.getAll():
                for i in range(0,len(self.__repo.getAll()[key])):
                    if (str(self.__repo.getAll()[key][i].getTime()).find(timp)) >=0:
                        print(self.__repo.getAll()[key][i].getTime(),": ",self.__repo.getAll()[key][i].getDescr())
                        ok = 0
            if ok:
                raise Exception
        except Exception:
            raise Exception("No time found")
        
    def descrSearch(self,descr):
        '''
        input : descr
        return : any descr that contains the input descr
        '''
        ok = 1;
        try:
            descr = descr.lower()
            for key in self.__repo.getAll():
                for i in range(0,len(self.__repo.getAll()[key])):
                    if (self.__repo.getAll()[key][i].getDescr().find(descr)) >=0:
                        print(self.__repo.getAll()[key][i].getDescr())
                        ok = 0
            if ok:
                raise Exception
        except Exception:
            raise Exception("No description found")
    
    def existentAct(self,id):
        '''
        input : id
        return : True if exists an activity with id from input
                 False, otherwise
        '''
        for key in self.__repo.getAll():
            if str(key) == str(id):
                return True
        return False
    
    def existentActPers(self,idA,idP):
        '''
        input : idActivity,idPerson
        return : True if exists an activity with id from input 
                        that contains a person with idPerson
                 False, otherwise
        '''
        for key in self.__repo.getAll():
            for i in range(0,len(self.__repo.getAll()[key])):
                if str(key) == str(idA) and str(self.__repo.getAll()[key][i].getPersId()) == str(idP):
                    return True
        return False
        
    def removePers(self,id):
        """
        Remove an entity from the list
        id - identifier
        
        check if id exists
        """
        lista = []
        ok = 1
        try:
            id = int(id)
        except Exception:
            raise activityRepositoryException("Id not found")
        for key in self.__repo.getAll():
            x = self.__repo.getAll()[key]
            for i in x:
                if int(i.getPersId()) == id:
                    month = i.getMonth()
                    day = i.getDay()
                    data = date(2018,month,day)
                    hour = i.getHour()
                    minute = i.getMinute()
                    obiect = Activity(int(key),i.getPersId(),data,time(hour,minute),str(i.getDescr()))                         
                    undo = FunctionCall(self.__repo.add,obiect)
                    redo = FunctionCall(self.__repo.removePersAct,(int(key),i.getPersId()))
                    op = Operation(redo,undo)
                    if ok:
                        cascaded = CascadedOperations()
                        ok = 0
                    cascaded.add(op)
                    undo = FunctionCall(self.__repoSt.add,self.__repoSt.get(id))
                    redo = FunctionCall(self.__repoSt.remove,id)
                    op = Operation(redo,undo)
                    cascaded.add(op)
                    self.__undoController.recordOperation(cascaded)
                    self.__repoSt.remove(id)
                    self.__repo.removePersAct((int(key),i.getPersId()))
        for key in self.__repo.getAll():
            x = self.__repo.getAll()[key]
            if len(x) == 0:
                self.__repo.remove(key)
        
    def busiestDays(self):
        '''
        make a new list with the busiest days in descending order
        '''
        ordered = {}
        toRet = {}
        ok = 0
        for key in self.__repo.getAll():
            try:
                if ordered[self.__repo.getAll()[key][0].getDate()]:
                    ok = 1
            except Exception:
                ok = 2
            if ok == 2:
                ordered[self.__repo.getAll()[key][0].getDate()] = len(self.__repo.getAll()[key])
            else:
                ordered[self.__repo.getAll()[key][0].getDate()] += len(self.__repo.getAll()[key])
        ordered = OrderedDict(sorted(ordered.items(),key = lambda t: t[1], reverse=True))
        for i in ordered:
            toRet[i] = ordered[i]
        return toRet
    
    def allPersons(self):
        '''
        make a new list with all the people, sorted in descending order by the number of their activities
        '''
        ordered = {}
        toRet = {}
        for key in self.__repo.getAll():
            for i in self.__repo.getAll()[key]:
                if i.getPersId() in ordered:
                    ordered[i.getPersId()] += 1
                else:
                    ordered[i.getPersId()] = 1
        ordered = OrderedDict(sorted(ordered.items(),key = lambda t: t[1], reverse=True))
        for i in ordered:
            toRet[i] = ordered[i]
        return toRet
    
    def upcomingAct(self,id):
        '''
         List all upcoming activities to which a given person will participate
        '''
        ordered = {}
        for key in self.__repo.getAll():
            for i in self.__repo.getAll()[key]:
                if str(i.getPersId()) == str(id):
                    if id not in ordered:
                        ordered[i.getPersId()] = [i]
                    else:
                        ordered[i.getPersId()].append((i))
        return ordered
    
    def dayActivities(self,id):
        '''
        Activities for a given day/week. List the activities for a given day, in the order of their
            start time, or their date/time
        '''
        print(id)
        ordered = {}
        for key in self.__repo.getAll():
            for i in self.__repo.getAll()[key]:
                if i.getDate() == str(id):
                    if id not in ordered:
                        ordered[id] = [i.getDescr()]
                    else:
                        ordered[id].append(i.getDescr())
        return ordered
    
    def getAll(self):
        '''
        returns the whole dictionary
        '''
        return self.__repo.getAll()

