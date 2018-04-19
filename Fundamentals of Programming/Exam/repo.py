from point import *
class Board:
	'''
	the board
	'''
	def __init__(self):
		self._b = [[0,0,0,0,0,0], [0,0,0,0,0,0], [0,0,0,0,0,0], [0,0,0,0,0,0], [0,0,0,0,0,0], [0,0,0,0,0,0]]
		self.player = 2
		self.no = 0

	def addPoint(self, point, player):
		x = point.getX()
		y = point.getY()
		if player:
			self._b[x][y] = self.player
		else:
			if self.player == 2:
				self._b[x][y] = 1
			else:
				self._b[x][y] = 2
		self.no += 1
		
	def trans(self, mat):
		for x in range(0,6):
			for y in range(0,6):
				self._b[x][y] = mat[x+1][y]

	def __str__(self):
		txt = "-------------"
		txt += '\n'
		d = {0:" |",1:"X|",2:"O|"}
		for x in range(0,6):
			txt += "|"
			for y in range(0,6):
				txt += d[self._b[x][y]]
			txt += '\n-------------\n'
		return txt

	def getBoard(self):
		return self._b