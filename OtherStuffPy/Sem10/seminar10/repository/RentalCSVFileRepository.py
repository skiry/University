'''
Created on Nov 20, 2016

@author: Arthur
'''
from seminar07.repository.Repository import Repository
from seminar07.repository.RepositoryException import RepositoryException
from datetime import date
from seminar07.domain.Rental import Rental

class RentalCSVFileRepository(Repository):
    def __init__(self, carRepo, clientRepo, fileName="rentals.txt"):
        Repository.__init__(self)
        self.__carRepo = carRepo
        self.__clientRepo = clientRepo
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

                rentalId = int(attrs[0])                
                clientId = int(attrs[1])
                carId = int(attrs[2])
                startDate = date(int(attrs[3].strip()), int(attrs[4].strip()), int(attrs[5].strip())) 
                endDate = date(int(attrs[6].strip()), int(attrs[7].strip()), int(attrs[8].strip())) 

                car = self.__carRepo.find(carId)
                client = self.__clientRepo.find(clientId)

                rental = Rental(rentalId, startDate, endDate, client, car)
                Repository.store(self, rental)
                line = f.readline().strip()
        except IOError:
            raise RepositoryException("Error saving file")
        finally:
            f.close()

    def __storeToFile(self):
        f = open(self.__fName, "w")
        rentals = Repository.getAll(self)
        for rental in rentals:
            start = rental.getStart()
            end = rental.getEnd()
            strf = str(rental.getId()) + "," + str(rental.getClient().getId()) + "," + str(rental.getCar().getId()) + "," + str(start.year) + "," + str(date.month) + "," + str(date.day) + "\n"
            f.write(strf)
        f.close()
