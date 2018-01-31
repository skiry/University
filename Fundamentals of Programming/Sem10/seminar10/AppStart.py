'''
Created on Dec 9, 2016

@author: Arthur
'''
from seminar10.repository.ClientCSVFileRepository import ClientCSVFileRepository
from repository.CarCSVFileRepository import CarCSVFileRepository
from repository.RentalCSVFileRepository import RentalCSVFileRepository
from repository.PickleFileRepository import PickleFileRepository

SETTINGS_FILE = "settings_text.properties"
# SETTINGS_FILE = "settings_binary.properties"

def readSettings():
    '''
    Reads the program's settings file
    output:
        A dictionary containing the program settings
    '''
    f = open(SETTINGS_FILE, "r")
    lines = f.read().split("\n")
    settings = {}
    
    for line in lines:
        setting = line.split("=")
        if len(setting) > 1:
            settings[setting[0]] = setting[1]
    f.close()
    return settings

settings = readSettings()

carRepo = None
clientRepo = None
rentalRepo = None

if 'CSV' == settings['repository']:
    carRepo = CarCSVFileRepository(settings['cars'])
    clientRepo = ClientCSVFileRepository(settings['clients'])
    rentalRepo = RentalCSVFileRepository(carRepo, clientRepo, settings['rentals'])

if 'binary' == settings['repository']:
    carRepo = PickleFileRepository(settings['cars'])
    clientRepo = PickleFileRepository(settings['clients'])
    rentalRepo = PickleFileRepository(settings['rentals'])

print('-' * 10 + " Clients " + '-' * 10)
print(clientRepo)
print('-' * 10 + " Cars " + '-' * 10)
print(carRepo)
print('-' * 10 + " Rentals " + '-' * 10)
print(rentalRepo)


'''
clientRepo = ClientCSVFileRepository()
print(clientRepo)

clientPickleRepo = PickleFileRepository("clients.pickle")
for c in clientRepo.getAll():
    clientPickleRepo.store(c)


carRepo = CarCSVFileRepository()
print(carRepo)

carPickleRepo = PickleFileRepository("cars.pickle")
for c in carRepo.getAll():
    carPickleRepo.store(c)

rentalRepo = RentalCSVFileRepository(carRepo, clientRepo)
print(rentalRepo)

rentalPickleRepo = PickleFileRepository("rentals.pickle")
for c in rentalRepo.getAll():
    rentalPickleRepo.store(c)
    
'''
