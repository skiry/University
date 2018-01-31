'''
Created on 15 nov. 2017

@author: Skiry
'''
from Controller.StudentController import *
from Controller.ActivityController import *
from Class.Activity import *

options = """ 
                  1. Add
                  2. Remove
                  3. Update
                  4. List
                  5. Search
                  6. Statistics
                  7. Undo
                  8. Redo
                  0. Exit
              """
otherOptions = """
                  1. Student
                  2. Activity
                """
printStatistics = """
                  1. Activities for a given day
                  2. Busiest days
                  3. Activities with a given person
                  4. All persons in descending order of the no of activities
                  """
class UI:
    '''
    Holds the ui entities
    '''
    def __init__(self,StudentController,ActivityController,UndoController):
        '''
        instantiation
        '''
        self.__StudentController = StudentController
        self.__ActivityController = ActivityController
        self.__UndoController = UndoController
    
    def menu(self):
        '''
        here we read the user's options
        '''
        print("Hi. Welcome to my program. ")
        while True:
            print(options)
            try:
                text = UI.getCommand()
                optOne = text[0]
                optTwo = text[1]
                if optOne == 0:
                    print("Have a great day")
                    self.__StudentController.closeSQL()
                    self.__ActivityController.closeSQL()
                    break
                elif optOne == 1:
                    if optTwo == 1:
                        self.__StudentController.add(self.addPerson())
                    elif optTwo == 2:
                        act = self.addActivity()
                        try:
                            self.checkPerson(act[1])
                            self.__ActivityController.add(act)
                        except Exception as exc:
                            print(exc)
                elif optOne == 2:
                    if optTwo == 1:
                        var = self.delPerson()
                        self.__ActivityController.removePers(var)
                    elif optTwo == 2:
                        self.__ActivityController.remove(self.delActivity(),True)
                elif optOne == 3:
                    if optTwo == 1:
                        self.__StudentController.update(self.updatePerson())
                    elif optTwo == 2:
                        act = self.updateActivity()
                        try:
                            if self.checkPerson(act[1]): 
                                self.__ActivityController.update(act)
                        except Exception as exc:
                            print(exc)
                elif optOne == 4:
                    if optTwo == 1:
                        print(self.__StudentController.__str__())
                    elif optTwo == 2:
                        for i in (self.__ActivityController.getAll()):
                            print("Activity number ",i)
                            x = self.__ActivityController.getAll()[i]
                            for j in x:
                                prsn = self.__StudentController.getAll()[j.getPersId()].getName()
                                print(prsn," with id ",j.getPersId()," on ", j.getDate()," at ",j.getTime()," has to do: ",j.getDescr())
                elif optOne == 5:
                    cmd = text[2]
                    if optTwo == 1:
                        if cmd == 1:
                            nume = input("Name: ")
                            self.__StudentController.nameSearch(nume)
                        elif cmd == 2:
                            no = input("Phone number: ")
                            self.__StudentController.noSearch(no)
                    elif optTwo == 2:
                        if cmd == 1:
                            data = input("Date < yyyy-mm-dd >: ")
                            self.__ActivityController.dateSearch(data)
                        elif cmd == 2:
                            timp = input("Time < hh:mm >: ")
                            self.__ActivityController.timeSearch(timp)
                        elif cmd == 3:
                            descr = input("Description: ")
                            self.__ActivityController.descrSearch(descr)  
                elif optOne == 6:
                    cmd = text[2]
                    if optTwo == 2:
                        ordered = self.__ActivityController.busiestDays()
                        for i in ordered:
                            print("On day ",i," there will be ",ordered[i]," activities!")
                    elif optTwo == 4:
                        ordered = self.__ActivityController.allPersons()
                        for i in self.__StudentController.getAll():
                            if i not in ordered:
                                ordered[i] = 0
                        for i in ordered:
                            for j in self.__StudentController.getAll():
                                if int(i) == int(j):
                                    print(self.__StudentController.getAll()[j].getName()," will participate to ",ordered[i]," activities!")
                    elif optTwo == 3:
                        try:
                            cmd = int(cmd)
                            if self.__StudentController.checkPerson(cmd)!=True:
                                raise Exception
                        except Exception:
                            raise Exception("Id inexistent")
                        ordered = self.__ActivityController.upcomingAct(cmd)
                        if len(ordered):
                            for i in ordered[cmd]:
                                print(self.__StudentController.getAll()[cmd].getName()," will participate to activity : ", i.getDescr())
                        else:
                            print(self.__StudentController.getAll()[cmd].getName()," has no events scheduled")
                        
                    elif optTwo == 1:
                        ordered = self.__ActivityController.dayActivities(cmd)
                        print("The following activities are scheduled: ")
                        for i in ordered:
                            for j in ordered[i]:
                             print(j)
                elif optOne == 7:
                    if self.__UndoController.undo():
                        print("Undo OK!")
                    else:
                        print("I do not have what to undo")
                elif optOne == 8:
                    if self.__UndoController.redo():
                        print("Redo OK!")
                    else:
                        print("I do not have what to redo")
            except activityRepositoryException as exc:
                print(exc)
            except studRepositoryException as exc:
                print(exc)
            except Exception as exc:
                print(exc)
    @staticmethod         
    def getCommand():  
        '''
        reads the command from the user and checks its validity
        '''
        choose = input("Command: ")
        choose2 = 0;
        cmd = 0;
        try:
            choose = int(choose)
            numberOfOptions = 8
            if choose not in range(0,numberOfOptions+1):
                raise Exception
            if choose in range(1,numberOfOptions-2):
                print(otherOptions)
                choose2 = input("Command: ")
                try:
                    choose2 = int(choose2)
                    if choose2 not in range(1,3):
                        raise Exception
                except Exception:
                    raise Exception
            if choose == 5:
                if choose2 == 1:
                    cmd = input("""
                                1. Name
                                2. Phone number
                                """)
                elif choose2 == 2:
                    cmd = input("""
                                1. Date 
                                2. Time 
                                3. Description
                                """)
                try:
                    cmd = int(cmd)
                    if cmd not in range(1,3) and choose2 == 1:
                        raise Exception
                    elif cmd not in range(1,4) and choose2 == 2:
                        raise Exception
                except Exception:
                    raise Exception
            if choose == 6:
                print(printStatistics)
                choose2 = input("Command: ")
                cmd2 = 0
                try:
                    choose2 = int(choose2)
                    if choose2 not in range(1,5):
                        raise Exception
                    if choose2 == 1:
                        cmd = input("Day: ")
                        cmd2 = input("Month: ")
                        try:
                            cmd = int(cmd)
                            cmd2 = int(cmd2)
                            if cmd not in range(1,32) or cmd2 not in range(1,13):
                                raise Exception
                        except Exception:
                            raise Exception("Day or month not ok")
                        cmd = date(2018,cmd2,cmd)
                    elif choose2 == 3:
                        cmd = input("Person: ")
                except Exception:
                    raise Exception
        except Exception:
            raise Exception
        return (choose,choose2,cmd)
    
    def addPerson(self):
        '''
        input for person obj
        '''
        id = input("ID:")
        name = input("Name: ")
        number = input("Phone no: ")
        address = input("Address: ")
        return (id,name,number,address)
    
    def updatePerson(self):
        '''
        input for person obj
        '''
        id = input("ID to update:")
        name = input("New name: ")
        number = input("New phone no: ")
        address = input("New address: ")
        return (id,name,number,address)
    
    def checkPerson(self,id):
        '''
        input: id
        return: true, if person with id exists
                exception, otherwise
        '''
        id = int(id)
        if self.__StudentController.checkPerson(id) == True:
            return True
        else:
            raise Exception("This person id does not exist at this moment")
                        
    def updateActivity(self):
        '''
        input for activity obj
        '''
        id = input("ID to update: ")
        pId = input("New person ID: ")
        month = input("New month: ")
        day = input("New day: ")
        hour = input("New hour: ")
        mins = input("New minute: ")
        descr = input("New description: ")
        return (id,pId,month,day,hour,mins,descr)
    
    def addActivity(self):
        '''
        input for activity obj
        '''
        id = input("ID: ")
        pId = input("Person ID: ")
        if self.__ActivityController.existentAct(id):
            return (id,pId,0,0,0,0,0)
        month = input("Month: ")
        day = input("Day: ") 
        hour = input("Hour: ")
        mins = input("Minute: ")
        descr = input("Description: ")
        return (id,pId,month,day,hour,mins,descr)
    
    def delPerson(self):
        '''
        input for removing person obj
        '''
        id = input("ID to delete: ")
        return id
    
    def delActivity(self):
        '''
        input for removing activity obj
        '''
        id = input("ID to delete: ")
        return id