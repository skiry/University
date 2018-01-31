'''
Created on 14 nov. 2017

@author: Skiry
'''
from Airport1 import addFlight, addDelay
from Airport1 import testInit
from Airport1 import deleteId
menu="""
     1. Add a flight
     2. Delete a flight
     3. Show all flights from a city
     4. Flight delays
     5. Exit
     """
def readCommand():
    '''
    Here we check if the written value is an INTEGER and is in [1,5], othwerwise
    we raise an exception
    '''
    x = input()
    try:
        x = int(x)
        if x not in range(1,6):
            raise ValueError
        else:
             return x
    except Exception:
        print("Write a number between 1 and 5 !")
        
def readFlight():
    '''
    Here we read the flight
    Input : code ( string )
            duration ( int ) -> minutes
            departure city ( string )
            destination city ( string )
    Output : -
    Return a list with the 4 params
    '''
    code = str(input("The code of the flight: "))
    duration = input("Duration of the flight: ")
    try:
        duration = int(duration)
        departure = str(input("Departure city: "))
        destination = str(input("Destination city: "))
        return (code,duration,departure,destination)
    except Exception:
        print("Must be an integer!")

def showAll(flights,city):
    '''
    Show all flights with a given departure city, sorted increasing by their dest city
    '''
    newList = []
    ok = 0
    for i in flights:
        if i[2] == city:
            newList.append(i)
            ok = 1
    if ok == 0:
        raise Exception
    sorted(newList)
    print(newList)
     
def UI():
    '''
    Here we get the option chosen by the user 
    '''
    flights = testInit()
    while True:
        print(menu)
        try:
            x = readCommand()
            if x == 5:
                print("Have a good day!")
                break
            elif x == 1:
                try:
                    flight = readFlight()
                    addFlight(flights,flight)
                    print(flights)
                except KeyError:
                    print("The strings must be > 3 and the duration > 20")
                except ValueError:
                    print("ID must be unique")
            elif x == 2:
                id = input("Code to delete: ")
                try:
                    deleteId(flights,id)
                except Exception:
                    print("Code not found")
            elif x == 3:
                city = input("Departure city: ")
                try:
                    showAll(flights,city)
                except Exception:
                    print("Departure city inexistent")
            elif x == 4:
                minutes = input("Minutes: ")
                try:
                    minutes = int(minutes)
                    city = input("City: ")
                    if minutes not in range(10,61):
                        raise ValueError
                    flights=addDelay(flights,minutes,city)
                except ValueError:
                    print("The number of minutes is not in the given range!")
                except KeyError:
                    print("City not found")
        except ValueError:
            print("Write a number between 1 and 5 !")
            
UI()