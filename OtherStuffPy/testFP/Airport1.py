'''
Created on 14 nov. 2017

@author: Skiry
'''
from copy import deepcopy
def testInit():
    airport = []
    airport.append(("W00Z3B",35,"Cluj-Napoca","Bucharest"))
    airport.append(("T01R2B",40,"Bucharest","Cluj-Napoca"))
    airport.append(("W00Z3B",35,"Madrid","Granada"))
    airport.append(("BAR8B",135,"Cluj-Napoca","Rome"))
    airport.append(("TWAR901",1200,"Paris","New York"))
    airport.append(("W113B",90,"Ouagadougou","Bali"))
    airport.append(("W98HH5",85,"Barcelona","Bucharest"))
    airport.append(("TW95110",70,"Malta","Sicilia"))
    airport.append(("BARI22",83,"Milano","Cluj-Napoca"))
    airport.append(("T00Z3B",100,"Satu-Mare","Bucharest"))
    return airport
    
def addFlight(flights,flight):
    '''
    With the list from the UI, add the flight to the flights list
    Check if the duration is less than 20 minutes
    Check if the strings have a length less than 3 characters
    '''
    try:
        code=flight[0]
        duration=flight[1]
        departure=flight[2]
        destination=flight[3]
        code=code.strip()
        departure=departure.strip()
        destination=destination.strip()
        if duration < 20 or len(code) < 3 or len(departure) < 3 or len(destination) < 3:
            raise KeyError
        for i in flights:
            if code == i[0]:
                raise ValueError
        flights.append(flight)
    except KeyError:
         raise KeyError
    
def testAddFlight():
    '''
    test function for addFlight
    '''
    flights = []
    addFlight(flights,("T01R2B",40,"Bucharest","Cluj-Napoca"))
    assert len(flights) == 1
    try:
        addFlight(flights,("T01M2B",10,"Bucharest","Cluj-Napoca"))
        assert False
    except Exception:
        assert True

def deleteId(flights,id):
    '''
    With the id from the UI, delete the flight with the given id
    Check if the code is valid -> delete it
    '''
    ok = 0
    for i in flights:
        if id == i[0]:
            ok = 1
            flights.remove(i)
    if ok == 0:
        raise Exception

def testDeleteId():
    '''
    test function for deleteId
    '''
    flights = testInit()
    deleteId(flights,"BAR8B")
    assert len(flights) == 9
    try:
        deleteId(flights,"Error")
        assert False
    except Exception:
        assert True

def addDelay(flights,minutes,city):
    ok = 0
    newL=[]
    for i in flights:
        if i[2] == city:
            ok = 1
            value=i[1]+minutes
            new =[i[0],value,i[2],i[3]]
            newL.append(new)
        else: newL.append(i)
    if ok == 0:
        raise KeyError
    return newL

def testProgram():
    '''
    run all test functions
    '''
    testAddFlight()
    testDeleteId()
testProgram()
