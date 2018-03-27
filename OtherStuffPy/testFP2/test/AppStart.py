'''
Created on 19 dec. 2017

@author: Skiry
'''
from Classes.Order import *
from Classes.Taxi import *
class UI:
    '''
    classdocs
    '''


    def __init__(self, drvC, ordC):
        '''
        Constructor
        '''
        self._drvC = drvC
        self._ordC = ordC
        
        
    def main(self):
        while True:
            try:
                prt = """
                1.Add an order. <id, dist>
                2. Display orders
                3. Compute the income of driver 'ID'
                """
                x = input(prt)
                try:
                    x = int(x)
                    if x < 1 or x > 3:
                        raise Exception("Invalid")
                except Exception as exc:
                    raise Exception(exc)
                if x == 1:
                    try:
                        a = int(input("Id: "))
                        b = int(input("Dist: "))
                        self._ordC.add(Order(a,b))
                    except Exception as exc:
                        raise Exception("Integers please")
                elif x == 2:
                    y = self._ordC.getAll()
                    for i in y:
                        for j in y[i]:
                            print("Order for driver ",j.getId()," with the distance",j.getDist())
                elif x == 3:
                    try:
                        nr = input("Id: ")
                        nr = int(nr)
                        print(self._drvC.getId(nr), "has an income of ", self._ordC.getSum(nr))
                    except Exception as exc:
                        raise Exception("Integers please")
            except Exception as exc:
                print(exc)
                
        