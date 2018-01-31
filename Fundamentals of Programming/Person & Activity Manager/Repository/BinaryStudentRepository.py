'''
Created on 11 dec. 2017

@author: Skiry
'''
from Repository.StudentRepository import StudentRepository
import pickle

class BinaryPersons(StudentRepository):
    '''
    repository for person class, in binary mode, with inheritance from the inmemory repo
    '''


    def __init__(self, fileName = "Persons.pickle"):
        '''
        Constructor
        '''
        StudentRepository.__init__(self)
        self.__fileName = fileName
        self.__readFromFile()
        
    def add(self, person):
        StudentRepository.add(self, person)
        self.__writeToFile()
        
    def remove(self, id):
        StudentRepository.remove(self, id)
        self.__writeToFile()
        
    def update(self, person):
        StudentRepository.update(self, person)
        self.__writeToFile()
        
    def __readFromFile(self):
        try:
            f = open(self.__fileName, "rb")
            self.__data = pickle.load(f)
            for i in self.__data:
                self.add(self.__data[i])
        except EOFError:
            # if the file is empty
            self.__data = {}
        except IOError as exc:
            raise exc
        finally:
            f.close()
    
    def __writeToFile(self):
        f = open(self.__fileName, "wb")
        pickle.dump(StudentRepository.getAll(self), f) #pickle.dump(self.__data, f)
        f.close()
        