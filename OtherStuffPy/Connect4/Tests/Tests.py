import sys
sys.path.append('./..')
from Class.Point import *
from Repo.Board import *
from Controller.Game import *
import unittest

#python3 -m unittest Tests.py 

class connectFourTest(unittest.TestCase):
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
		puncte = [Point(0,5), Point(0,6), Point(6,5), Point(6,6), Point(7,6), Point(7,5), Point(1,4)]
		coords = [[0,5], [0,6], [6,5], [6,6], [7,6], [7,5], [1,4]]
		for i in range(0,len(puncte)):
			point = puncte[i]
			self.assertTrue(point.getX() == coords[i][0])
			self.assertTrue(point.getY() == coords[i][1])
		board = Board()
		game = Game(board)
		board.addPoint(puncte[0],0)
		board.addPoint(puncte[1],1)
		board.addPoint(puncte[2],0)
		board.addPoint(puncte[3],1)
		board.addPoint(puncte[4])
		board.addPoint(puncte[5],1)
		board.addPoint(puncte[6])

		ver0 = [0,2,4,6]
		ver1 = [1,3,5]
		for x in range(0,len(board._dict[0])):
			self.assertTrue(board._dict[0][x] == puncte[ver0[x]])

		for x in range(0,len(board._dict[1])):
			self.assertTrue(board._dict[1][x] == puncte[ver1[x]])

		self.assertTrue(board.changePlayer(0) == 1)
		self.assertTrue(board.changePlayer(1) == 0)

		moves = board.avMoves()
		notOk = [1,2,3,7]
		ok = [4,5,6,8]
		for x in notOk:
			self.assertFalse(x in moves)
		for x in ok:
			self.assertTrue(x in moves)

		self.assertFalse(board.inRange(Point(100,100)))
		self.assertFalse(board.inRange(Point(6,5)))
		self.assertTrue(board.inRange(Point(0,0)))

		self.assertFalse(board.okPoint(Point(12,5)))

		self.assertTrue(game.makeMoveUser(Point(3,3)) == None)
		board.addPoint(Point(5,4))
		board.addPoint(Point(4,3))

		moves = board.avMoves()
		self.assertTrue(game.makeMoveAI()[0] == 7)

if __name__ == '__main__':
	tests = unittest.TestLoader().discover('.')
	unittest.TextTestRunner(verbosity = 2).run(tests)