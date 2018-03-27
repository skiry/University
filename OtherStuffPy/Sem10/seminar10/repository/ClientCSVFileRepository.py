'''
Created on Nov 20, 2016

@author: Arthur
'''
from seminar07.repository.Repository import Repository
from seminar07.domain.Client import Client
from seminar07.repository.RepositoryException import RepositoryException

class ClientCSVFileRepository(Repository):
    def __init__(self, fileName="clients.txt"):
        Repository.__init__(self)
        self.__fName = fileName
        self.__loadFromFile()
    
    def store(self, client):
        Repository.store(self, client)
        self.__storeToFile()
    
    def delete(self, clientId):
        Repository.delete(self, clientId)
        self.__storeToFile()        
    
    def update(self, newClient):
        Repository.update(self, newClient)
        self.__storeToFile()
    
    def __loadFromFile(self):
        try:
            f = open(self.__fName, "r")
            line = f.readline().strip()
            while line != "":
                attrs = line.split(",")
                client = Client(int(attrs[0]), attrs[1], attrs[2])
                Repository.store(self, client)
                line = f.readline().strip()
        except IOError:
            raise RepositoryException("Error saving file")
        finally:
            f.close()
        
    def __storeToFile(self):
        f = open(self.__fName, "w")
        clients = Repository.getAll(self)
        for client in clients:
            strf = str(client.getId()) + "," + client.getCNP() + "," + client.getName() + "\n"
            f.write(strf)
        f.close()
