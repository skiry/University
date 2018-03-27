'''
Created on 19 dec. 2017

@author: Skiry
'''
from Repo.DriversRepo import DrvRepo
from Repo.OrdersRepo import OrdRepo
from Ctrl.DrvController import *
from Ctrl.OrdController import *
from test.AppStart import *


def readDrivers():
    f = open("drivers.txt", "r")
    lines = f.read().split('\n')
    for line in lines:
        linie = line.split(",")
        id = int(linie[0])
        name = linie[1]
        taxiRepo.add(Driver(id,name))
    f.close()
    
def readOrders():
    f = open("orders.txt", "r")
    lines = f.read().split('\n')
    for line in lines:
        linie = line.split(",")
        id = int(linie[0])
        dist = int(linie[1])
        ordersRepo.add(Order(id,dist))
    f.close()
    
taxiRepo = DrvRepo()
ordersRepo = OrdRepo()
readDrivers()
readOrders()
taxiCtrl = Controller(taxiRepo)
ordersCtrl = OrdersCtrl(taxiRepo, ordersRepo)
ui = UI(taxiCtrl, ordersCtrl)
ui.main()
