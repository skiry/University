from repo import *
from ctrl import *
from main import *
import unittest

#python3 -m unittest Tests.py 

class gameTest(unittest.TestCase):
	"""
	asserts for the main class 'point', repo and controller
	"""
	def setUp(self):
		unittest.TestCase.setUp(self)

	def tearDown(self):
		unittest.TestCase.tearDown(self)

	def testing(self):
		'''
		the testing function
		'''
		point = Point(1,2,3,4,5,6)
		self.assertTrue(point.getL1() == 1)
		self.assertTrue(point.getC1() == 2)
		self.assertTrue(point.getL2() == 3)
		self.assertTrue(point.getC2() == 4)
		self.assertTrue(point.getL3() == 5)
		self.assertTrue(point.getC3() == 6)
		board = Repository()
		game = Controller(board)
		#self.assertRaises(game.validate("A2C4F7", Exception)
		game.addShip("A2B2C2")
		with self.assertRaises(Exception):
			game.addShip("A2B2C2")

		with self.assertRaises(Exception):
			game.checkMove("R4")

		with self.assertRaises(Exception):
			game.checkMove("C6")

		with self.assertRaises(Exception):
			game.checkMove("RR")

		with self.assertRaises(Exception):
			game.validate("R4A4C4")

		with self.assertRaises(Exception):
			game.validate("D4A4C6")

		with self.assertRaises(Exception):
			game.validate("RRA4C4")
if __name__ == '__main__':
	tests = unittest.TestLoader().discover('.')
	unittest.TextTestRunner(verbosity = 2).run(tests)