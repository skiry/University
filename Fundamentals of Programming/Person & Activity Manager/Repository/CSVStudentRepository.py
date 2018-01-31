'''
Created on 10 dec. 2017

@author: Skiry
'''
from Repository.StudentRepository import StudentRepository
from Class.Person import Person
class CSVPersons(StudentRepository):
    '''
    repository for persons, with inheritance from the inmemory repository
    '''


    def __init__(self, fileName = "Persons.txt"):
        '''
        Constructor
        '''
        StudentRepository.__init__(self)
        self.__fileName = fileName
        self.__loadFromFile()
    
    def add(self, person):
        StudentRepository.add(self, person)
        self.__storeToFile()
    
    def remove(self, id):
        StudentRepository.remove(self, id)
        self.__storeToFile()
        
    def update(self, person):
        StudentRepository.update(self, person)
        self.__storeToFile()
    
    def __storeToFile(self):
        f = open(self.__fileName, "w")
        persons = StudentRepository.getAll(self)
        for person in persons:
            x = persons[person]
            txt = str(person) + ";" + x.getName() + ";" + x.getNumber() + ";" + x.getAddress() + '\n'
            f.write(txt)
        f.close()
        
    def __loadFromFile(self):
        f = open(self.__fileName, "r")
        lines = f.read().split('\n')
        for line in lines:
            elements = line.split(';')
            if line != "":
                pers = Person(int(elements[0]),elements[1],elements[2],elements[3])
                StudentRepository.add(self, pers)
        f.close()