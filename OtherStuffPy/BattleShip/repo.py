from main import *
class Repository:
	'''
	docstring for Repository
	'''
	def __init__(self):
		self._board = [[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0]]
		self._AI = [[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0]]
		self._lista = {}
		self._cheats = 0
		self._gasitePl = 0
		self._gasiteAI = 0

	def makeMovePlayer(self, move):
		'''
		add player's move to the table
		'''
		x = move.getL1()
		y = move.getC1()
		if self._AI[y][x] == 1:
			self._AI[y][x] = 2
			self._gasitePl += 1
		else:
			self._AI[y][x] = 3

	def makeMoveAI(self, move):
		'''
		add ai's move to the table
		'''
		x = move.getL1()
		y = move.getC1()
		if self._board[y][x] == 1:
			self._board[y][x] = 2
			self._gasiteAI += 1
		else:
			self._board[y][x] = 3

	def addAISheep(self, point):
		'''
		add ai's ship to the table
		'''
		x = point.getL1()
		y = point.getC1()
		x = int(x)
		y = int(y)
		self._AI[y][x] = 1

		x = point.getL2()
		y = point.getC2()
		x = int(x)
		y = int(y)
		self._AI[y][x] = 1

		x = point.getL3()
		y = point.getC3()
		x = int(x)
		y = int(y)
		self._AI[y][x] = 1

	def addSheep(self, point):
		'''
		add player's ship to the table
		'''
		puneInapoi = 0
		if 2 in self._lista:
			if 1 in self._lista:
				obj = self._lista[1]

				x = obj.getL1()
				y = obj.getC1()
				x = int(x)
				y = int(y)
				self._board[y][x] = 0
				x = obj.getL2()
				y = obj.getC2()
				x = int(x)
				y = int(y)
				self._board[y][x] = 0
				x = obj.getL3()
				y = obj.getC3()
				x = int(x)
				y = int(y)
				self._board[y][x] = 0

		x = point.getL1()
		y = point.getC1()
		x = int(x)
		y = int(y)
		if self._board[y][x] == 1:
			puneInapoi = 1
		x = point.getL2()
		y = point.getC2()
		x = int(x)
		y = int(y)
		if self._board[y][x] == 1:
			puneInapoi = 1
		x = point.getL3()
		y = point.getC3()
		x = int(x)
		y = int(y)
		if self._board[y][x] == 1:
			puneInapoi = 1

		if puneInapoi:
			if 2 in self._lista:
				if 1 in self._lista:
					obj = self._lista[1]

					x = obj.getL1()
					y = obj.getC1()
					x = int(x)
					y = int(y)
					self._board[y][x] = 1
					x = obj.getL2()
					y = obj.getC2()
					x = int(x)
					y = int(y)
					self._board[y][x] = 1
					x = obj.getL3()
					y = obj.getC3()
					x = int(x)
					y = int(y)
					self._board[y][x] = 1
			raise ValueError("Ship already there")

		x = point.getL1()
		y = point.getC1()
		x = int(x)
		y = int(y)
		x = point.getL1()
		y = point.getC1()
		x = int(x)
		y = int(y)
		self._board[y][x] = 1

		x = point.getL2()
		y = point.getC2()
		x = int(x)
		y = int(y)
		self._board[y][x] = 1

		x = point.getL3()
		y = point.getC3()
		x = int(x)
		y = int(y)
		self._board[y][x] = 1
		self._board[y][x] = 1

		x = point.getL2()
		y = point.getC2()
		x = int(x)
		y = int(y)
		self._board[y][x] = 1

		x = point.getL3()
		y = point.getC3()
		x = int(x)
		y = int(y)
		self._board[y][x] = 1

		if 1 not in self._lista:
			self._lista[1] = point
		elif 2 not in self._lista:
			self._lista[2] = point
		else:
			self._lista[1] = self._lista[2]
			self._lista[2] = point

	def __str__(self):
		'''
		string function to print correspondingly
		'''
		text = "  ABCDEF   ABCDEF"
		text += '\n'
		dicti = {0:"0 ", 1:"1 ", 2:"2 ", 3:"3 ", 4:"4 ", 5:"5 "}
		afis = {0:".", 1:"+", 2:"X",3:"O"}
		normal = {0:".", 1:".", 2:"X",3:"O"}
		cheats = {0:".", 1:"+", 2:"X",3:"O"}
		for x in range(0, 6):
			text += dicti[x]
			for y in range(0, 6):
				text += afis[self._board[x ][y]]
			text += " "
			text += dicti[x]
			for y in range(0,6):
				if self._cheats == 0:
					text += normal[self._AI[x][y]]
				else:
					text += cheats[self._AI[x][y]]
			text += '\n'
		return text

		

