'''
Created on 15 nov. 2017

@author: Skiry
'''
from Repository.StudentRepository import *
from Controller.UndoController import *
from Class.Person import *
class StudentController:
    '''
    The functions that will work with the studRepository
    We have the functions which will add,remove,update a student
         and print the list of students
    '''
    def __init__(self,repo,UndoController):
        """
        Constructor for controller class
        We also have the undo list created here.
        """
        self.__repo = repo
        self.__undoController = UndoController
        
    def closeSQL(self):
        self.__repo._closeSQL()
        
    def get(self,index):
        return self.__repo.get(index)
        
    def add(self,typeOf):
        """
        Add an entity to a list
        typeOf - object of type student
        
        check if id is unique
        check if phone number is unique
        """
        id = typeOf[0]
        name = typeOf[1]
        number = typeOf[2]
        address = typeOf[3]
        try:
            id = int(id)
        except Exception:
            raise studRepositoryException("Integer id")
        
        if self.__repo.find(id):
            raise studRepositoryException("This id is already existent")
        if self.__repo.checkNumber(number,id):
            raise studRepositoryException("The phone number is taken")
        noCheck = str(number)
        if len(noCheck) != 10 or noCheck[0] != '0':
            raise studRepositoryException("Phone number invalid")
        
        try:
            number = int(number)
            number = str(number)
            number = str(0)+str(number)
        except Exception:
            raise studRepositoryException("Just digits for phone number")
        self.__repo.add(Person(id,name,number,address))
        undo = FunctionCall(self.__repo.remove,id)
        redo = FunctionCall(self.__repo.add,Person(id,name,number,address))
        op = Operation(redo,undo)
        self.__undoController.recordOperation(op)
    
    def remove(self,id,recordForUndo = True):
        """
        Remove an entity from the list
        id - identifier
        
        check if id exists
        """
        try:
            id = int(id)
            if self.__repo.find(id):
                if recordForUndo:
                    redo = FunctionCall(self.__repo.remove,id)
                for i in self.__repo.getAll():
                    if i == id:
                        if recordForUndo:
                            undo = FunctionCall(self.__repo.add,Person(id,self.__repo.getAll()[i].getName(),self.__repo.getAll()[i].getNumber(),self.__repo.getAll()[i].getAddress()))
                if recordForUndo:
                    op = Operation(redo,undo)
                    self.__undoController.recordOperation(op)
                self.__repo.remove(id)
            else:
                raise Exception
        except Exception as exc:
            raise studRepositoryException("Id not found")
    
    def __str__(self):
        """
        String representation of this repository
        """
        txt = ""
        x = self.__repo.getAll()
        for key in x:
            txt += "Person " + str(key) + " named " +str(x[key].getName()) + " has the phone number " + str(x[key].getNumber()) + " and lives on " + str(x[key].getAddress())+ '\n'
        return txt
    
    def update(self,typeOf):
        """
        Update an entity from the list
        typeOf - object of type student
        
        check if id exists
        check if new number is ok
        """
        id = typeOf[0]
        name = typeOf[1]
        number = typeOf[2]
        address = typeOf[3]
        try:
            id = int(id)
        except Exception:
            raise studRepositoryException("Integer id")
        
        if self.__repo.find(id) == False:
            raise studRepositoryException("This id is inexistent")
        if self.__repo.checkNumber(number,id):
            raise studRepositoryException("The phone number is taken")
        noCheck = str(number)
        if len(noCheck) != 10 or noCheck[0] != '0':
            raise studRepositoryException("Phone number invalid")
        try:
            numbert = int(number)
        except Exception:
            raise Exception("Just digits for phone number")
        obiect = Person(id,name,number,address)
        redo = FunctionCall(self.__repo.update,obiect)
        for i in self.__repo.getAll():
            if i == id:
                undo = FunctionCall(self.__repo.update,Person(id,self.__repo.getAll()[i].getName(),self.__repo.getAll()[i].getNumber(),self.__repo.getAll()[i].getAddress()))
        op = Operation(redo,undo)
        self.__undoController.recordOperation(op)
        self.__repo.update(obiect)
        
    def checkPerson(self,id):
        '''
        check if a person exists
        '''
        if self.__repo.find(id) == True:
                return True
        raise Exception("Person id not found")
    
    def nameSearch(self,name):
        '''
        input : text
        return : any text that contains the input text
        '''
        ok = 1;
        try:
            for key in self.__repo.getAll():
                if (self.__repo.getAll()[key].getName().lower().find(name.lower())) >=0:
                    print(self.__repo.getAll()[key].getName())
                    ok = 0
            if ok:
                raise Exception
        except Exception:
            raise Exception("No name found")
        
    def noSearch(self,no):
        '''
        input : phone number
        return : any number that contains the input number
        '''
        ok = 1;
        try:
            for key in self.__repo.getAll():
                if (self.__repo.getAll()[key].getNumber().find(no)) >=0:
                    print(self.__repo.getAll()[key].getNumber())
                    ok = 0
            if ok:
                raise Exception
        except Exception:
            raise Exception("No number found")
        
    def getAll(self):
        '''
        returns the whole dictionary
        '''
        return self.__repo.getAll()

