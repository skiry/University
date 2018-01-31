'''
Created on 11 dec. 2017

@author: Skiry
'''
from Repository.ActivityRepository import ActivityRepository
import pickle
class BinaryActivities(ActivityRepository):
    '''
    repository for activities with binary files, with inheritance from the inmemory repo
    '''


    def __init__(self, fileName = "Activities.pickle"):
        '''
        Constructor
        '''
        ActivityRepository.__init__(self)
        self.__fileName = fileName
        self.__readFromFile()
        
    def add(self, person):
        ActivityRepository.add(self, person)
        self.__writeToFile()
        
    def remove(self, id):
        ActivityRepository.remove(self, id)
        self.__writeToFile()
        
    def update(self, person):
        ActivityRepository.update(self, person)
        self.__writeToFile()
        
    def __readFromFile(self):
        try:
            f = open(self.__fileName, "rb")
            self.__data = pickle.load(f)
            for i in self.__data:
                for j in self.__data[i]:
                    self.add(j)
        except EOFError:
            # if the file is empty
            self.__data = {}
        except IOError as exc:
            raise exc
        finally:
            f.close()
    
    def __writeToFile(self):
        f = open(self.__fileName, "wb")
        pickle.dump(ActivityRepository.getAll(self), f) #pickle.dump(self.__data, f)
        f.close()
        