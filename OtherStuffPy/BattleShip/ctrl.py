from repo import *
from main import *
import random
class Controller:
	'''
	docstring for Controller
	'''
	def __init__(self, board):
		self._board = board


	def addShip(self, punct):
		'''
		adding a ship to the board
		'''
		x = ord(punct[0]) - 65
		y = punct[1]
		z = ord(punct[2]) - 65
		q = ord(punct[4]) - 65
		t = punct[3]
		r = punct[5]
		point = Point(x, y, z, t ,q ,r)
		try:
			self._board.addSheep(point)
		except Exception as exc:
			raise Exception(exc)

	def AImove(self):
		'''
		ai's move
		'''
		x = random.randint(0,5)
		y = random.randint(0,5)
		self._board.makeMoveAI(Point(x,y,0,0,0,0))

	def AIships(self):
		'''
		ai choosing his ships randomly
		'''
		x = random.randint(0,3)
		y = random.randint(0,1)
		z = random.randint(0,3)
		if y == 1:
			pct = Point(x,z,x+1,z,x+2,z)
		else:
			pct = Point(x,z,x,z+1,x,z+2)

		self._board.addAISheep(pct)
		if x == 0:
			x = 1
		else:
			x = 0
		if z == 0:
			z = 2
		else:
			z -= 1

		if y == 1:
			pct = Point(x,z,x+1,z,x+2,z)
		else:
			pct = Point(x,z,x,z+1,x,z+2)

		self._board.addAISheep(pct)

	def checkMove(self, move):
		'''
		check if a move is correct and in range
		'''
		litere = ["a","b","c","d","e","f"]
		print(move)
		try:
			if move[0].lower() not in litere:
				raise ValueError("Choose a good letter!")
			x = int(move[1])
			if x not in range(0,6):
				raise ValueError("Choose a good number!")
		except Exception as exc:
			raise Exception(exc)

	def makeMove(self, move):
		'''
		player's move
		'''
		x = ord(move[0]) - 65
		y = int(move[1])
		self._board.makeMovePlayer(Point(x,y,0,0,0,0))

	def validate(self, punct):
		'''
		validation of a point. if it is in board and not overlapping
		'''
		try:
			litere = ["a","b","c","d","e","f"]
			cifre = [0, 1, 2, 3, 4, 5]
			inLine = 0
			inColumn = 0
			if len(punct) != 6:
				return False

			for i in range(0,6):
				if i%2:
					try:
						cifra = punct[i]
						cifra = int(cifra)
						if cifra not in cifre:
							raise Exception
					except Exception:
						raise Exception("Respect the rules")
						return False
				else:
					if punct[i].lower() not in litere:
						raise Exception("Respect the rules")
						return False

			if int(punct[1]) == int(punct[3]) == int(punct[5]):
				inLine = 1
			if int(punct[1]) + 1 == int(punct[3]):
				if int(punct[3]) + 1 == int(punct[5]):
					inLine = 2
			if int(punct[5]) + 1 == int(punct[3]):
				if int(punct[3]) + 1 == int(punct[1]):
					inLine = 3
			if inLine not in [1,2,3]:
				return False

			if ord(punct[0]) == ord(punct[2]) == ord(punct[4]):
				inColumn = 1

			if ord(punct[0]) + 1 == ord(punct[2]):
				if ord(punct[2]) + 1 == ord(punct[4]):
					inColumn = 2

			if ord(punct[4]) + 1 == ord(punct[2]):
				if ord(punct[2]) + 1 == ord(punct[0]):
					inColumn = 3

			if inColumn not in [1,2,3]:
				return False

			if inLine == inColumn:
				return False

			return True

		except Exception as exc:
			raise Exception(exc)

	def getBoard(self):
		'''
		return the board
		'''
		return self._board