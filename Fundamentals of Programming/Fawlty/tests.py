from repo import *
from ctrl import *
from reservations import *
import unittest

#python3 -m unittest Tests.py 

class fawltyTest(unittest.TestCase):
	"""
	asserts for the repo and the controller
	"""
	def setUp(self):
		unittest.TestCase.setUp(self)

	def tearDown(self):
		unittest.TestCase.tearDown(self)

	def testing(self):
		'''
		the testing function
		'''
		repoRsv = repoReservations()
		repoRoom = repoRooms()
		ctrlRsv = ctrlReservations(repoRsv,repoRoom)


		ctrlRoom = ctrlRooms(repoRoom)
		with self.assertRaises(Exception):
			ctrlRsv.delRsv(1923)

		with self.assertRaises(Exception):
			repoRsv.delRsv(1923)
		Reservatie = Reservation(1180,1,"Albu",2,"15.02","19.02")

		ctrlRsv.addReserv(Reservatie)
		Reservatie = Reservation(1182,1,"Albul",2,"18.02","19.02")
		ctrlRsv.addReserv(Reservatie)

		self.assertFalse(ctrlRsv.createNo() in ctrlRsv.getAll())

		with self.assertRaises(Exception):
			repoRsv.delRsv(9124)


		Reservatie = Reservation(1183,1,"Aul",2,"90.02","19.02")
		with self.assertRaises(Exception):
			ctrlRsv.chcekRsv(Reservatie)

		Reservatie = Reservation(1183,1,"Aul",2,"20.02","39.02")
		with self.assertRaises(Exception):
			ctrlRsv.chcekRsv(Reservatie)

		Reservatie = Reservation(1183,1,"",2,"90.02","19.02")
		with self.assertRaises(Exception):
			ctrlRsv.chcekRsv(Reservatie)

		Reservatie = Reservation(1183,1,"Aul",9,"90.02","19.02")
		with self.assertRaises(Exception):
			ctrlRsv.chcekRsv(Reservatie)

		Reservatie = Reservation(1183,1,"Aul",0,"90.02","19.02")
		with self.assertRaises(Exception):
			ctrlRsv.chcekRsv(Reservatie)

if __name__ == '__main__':
	unittest.main()
	# tests = unittest.TestLoader().discover('.')
	# unittest.TextTestRunner(verbosity = 2).run(tests)