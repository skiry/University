from repo import *
from ctrl import *
from point import *
import unittest

#python3 -m unittest Tests.py 

class gameTest(unittest.TestCase):
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
		repo = Board()
		game = Game(repo)
		points = [Point(1,2), Point(1,3), Point(1,4),Point(1,5)]
		for x in points:
			'''
			check the valid moves
			'''
			self.assertTrue(x.getX() == 1)
		points2 = [Point(6,2), Point(9,3), Point(1,8),Point(11,5)]
		for y in points2:
			with self.assertRaises(Exception):
				game.checkMove(y)
		for counter in range(35):
			'''
			check full table
			'''
			self.assertTrue(game.chooseRandom())
		for counter in range(2):
			'''
			this should be false, table is full
			'''
			self.assertFalse(game.chooseRandom())

		self.assertTrue(Point(1,2).getX() == 1)
		self.assertTrue(Point(1,2).getY() == 2)
		self.assertTrue(Point(1,3).getX() == 1)
		self.assertTrue(Point(1,3).getY() == 3)
		self.assertTrue(Point(1,4).getX() == 1)
		self.assertTrue(Point(1,4).getY() == 4)
		self.assertTrue(Point(1,5).getX() == 1)
		points2 = [Point(6,2), Point(9,3), Point(1,8),Point(11,5)]
		for y in points2:
			with self.assertRaises(Exception):
				game.checkMove(y)

if __name__ == '__main__':
	unittest.main()
	# tests = unittest.TestLoader().discover('.')
	# unittest.TextTestRunner(verbosity = 2).run(tests)