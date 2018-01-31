'''
Created on Nov 22, 2016

@author: Arthur
'''
from seminar07.repository.Repository import Repository

import pickle

class PickleFileRepository(Repository):
    def __init__(self, fileName="repo.pickle"):
        Repository.__init__(self)
        self.__fName = fileName
        self.__loadFromFile()
    
    def store(self, client):
        Repository.store(self, client)
        self.__storeToFile()
     
    def delete(self, clientId):
        Repository.delete(self, clientId)
        self.__storeToFile()        
 
    def update(self, client):
        Repository.update(self, client)
        self.__storeToFile()

    def __loadFromFile(self):
        f = open(self.__fName, "rb")
        
        """
        You cannot unpickle an empty file
            - EOFError means the file is empty
            - Exception means no file, not accessible and so on...
            - finally makes sure we close the input file, regardless of error
        """
        try:
            self._objects = pickle.load(f)
        except EOFError:
            self._objects = {}
        except Exception as e:
            raise e
        finally:
            f.close()

    def __storeToFile(self):
        f = open(self.__fName, "wb")
        pickle.dump(self._objects, f)
        f.close()