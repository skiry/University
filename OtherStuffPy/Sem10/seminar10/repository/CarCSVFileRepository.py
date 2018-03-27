'''
Created on Nov 20, 2016

@author: Arthur
'''
from seminar10.repository.Repository import Repository
from seminar10.repository.RepositoryException import RepositoryException
from seminar10.domain.Car import Car

class CarCSVFileRepository(Repository):
    def __init__(self, fileName="cars.txt"):
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
                client = Car(int(attrs[0]), attrs[1], attrs[2], attrs[3])
                Repository.store(self, client)
                line = f.readline().strip()
        except IOError:
            raise RepositoryException("Error saving file")
        finally:
            f.close()
        
    def __storeToFile(self):
        f = open(self.__fName, "w")
        cars = Repository.getAll(self)
        for car in cars:
            strf = str(car.getId()) + "," + car.getLicenseNumber() + "," + car.getMake() + "," + car.getModel() + "\n"
            f.write(strf)
        f.close()
