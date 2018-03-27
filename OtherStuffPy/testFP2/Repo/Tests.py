'''
Created on 19 dec. 2017

@author: Skiry
'''
import unittest
from Classes import Taxi,Order
from Repo.DriversRepo import *
from Repo.OrdersRepo import *

class Test(unittest.TestCase):


    def setUp(self):
        unittest.TestCase.setUp(self)

    def tearDown(self):
        unittest.TestCase.tearDown(self)

    def testName(self):
        taxiRepo = DrvRepo()
        ordersRepo = OrdRepo()
        driver1 = Driver(1,"alex")
        taxiRepo.add(driver1)
        self.assertTrue(taxiRepo.getId(1) == "alex")
        self.assertFalse(taxiRepo.getId(1) == "marian")
        order1 = Order(1,10)
        ordersRepo.add(order1)
        #self.assertTrue(ordersRepo.getAll() == )