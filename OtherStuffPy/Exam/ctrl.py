from point import *
from repo import *
from random import randint
class Game:
	def __init__(self, board):
		self._g = board

	def checkMove(self, pct):
		try:
			x = int(pct.getX())
		except Exception:
			raise Exception
		y = pct.getY()
		if x not in range (0,6) or y not in range(0,6):
			raise ValueError("Point out of range")
		t = self._g.getBoard()
		if t[x][y]:
			raise ValueError("Place not free")

	def addPoint(self, pct, player):
		self._g.addPoint(pct, player)

	def block(self):
		ygrec = self.checkWin(4)
		if ygrec[0] == True:
			try:
				if ygrec[3] == 0:
					print("e 0")
					self.checkMove(Point(ygrec[1],ygrec[2]+1))
					self.addPoint(Point(ygrec[1],ygrec[2]+1),0)
				elif ygrec[3] == 1:
					print("e 1")
					self.checkMove(Point(ygrec[1]+1,ygrec[2]))
					self.addPoint(Point(ygrec[1]+1,ygrec[2]),0)
				elif ygrec[3] == 5:
					print("e 5")
					self.checkMove(Point(ygrec[1]+1,ygrec[2]+1))
					self.addPoint(Point(ygrec[1]+1,ygrec[2]+1),0)
				elif ygrec[3] == 6:
					print("e 6")
					self.checkMove(Point(ygrec[1]-1,ygrec[2]-1))
					self.addPoint(Point(ygrec[1]-1,ygrec[2]-1),0)
				return True
			except Exception:
				pass
		return False

	def checkWin(self, nr):
		y = self._g.getBoard()
		nr = nr - 1

		for x in range(0,6):
			cont = 0
			posx = 0
			posy = 0
			ant = 0
			for j in range(0,6):
				if y[x][j] == ant and y[x][j]:
					cont += 1
				else:
					cont -= 1
				ant = y[x][j]
				if cont == nr:
					posx = x
					posy = j
			if cont == nr:
				return [True,posx,posy,0]

		y = self._g.getBoard()
		for x in range(0,6):
			cont = 0
			posx = 0
			posy = 0
			ant = 0
			for j in range(0,6):
				if y[j][x] == ant and y[j][x]:
					cont += 1
				else:
					cont -= 1
				ant = y[j][x]
				if cont == nr:
					posx = j
					posy = x
			if cont == nr:
				return [True,posx,posy,1]

		y = self._g.getBoard()
		a = 0
		b = 1
		cont = 0
		posx = 0
		posy = 0
		ant = 0
		for cnt in range(0,5):
			if y[a][b] == ant and y[a][b]:
				cont += 1
			else:
				cont -= 1
			ant = y[a][b]
			if cont == nr:
				posx = a
				posy = b
			a += 1
			b += 1
		if cont == nr:
			return [True,posx,posy,5]
		y = self._g.getBoard()
		a = 1
		b = 0
		cont = 0
		posx = 0
		posy = 0
		ant = 0
		for cnt in range(0,nr):
			if y[a][b] == ant and y[a][b]:
				cont += 1
			else:
				cont -= 1
			ant = y[a][b]
			if cont == nr:
				posx = a
				posy = b
			a += 1
			b += 1
		if cont == nr:
			return [True,posx,posy,5]
		y = self._g.getBoard()
		a = 0
		b = 0
		cont = 0
		posx = 0
		posy = 0
		ant = 0
		for cnt in range(0,6):
			if y[a][b] == ant and y[a][b]:
				cont += 1
			else:
				cont -= 1
			ant = y[a][b]
			if cont == nr:
				posx = a
				posy = b
			a += 1
			b += 1
		if cont == nr:
			return [True,posx,posy,5]
		y = self._g.getBoard()
		a = 5
		b = 0
		cont = 0
		posx = 0
		posy = 0
		ant = 0
		for cnt in range(0,6):
			if y[a][b] == ant and y[a][b]:
				cont += 1
			else:
				cont -= 1
			ant = y[a][b]
			if cont == nr:
				posx = a
				posy = b
			a -= 1
			b += 1
		if cont == nr:
			return [True,posx,posy,6]
		y = self._g.getBoard()
		a = 5
		b = 1
		cont = 0
		posx = 0
		posy = 0
		ant = 0
		for cnt in range(0,5):
			if y[a][b] == ant and y[a][b]:
				cont += 1
			else:
				cont -= 1
			ant = y[a][b]
			if cont == nr:
				posx = a
				posy = b
			a -= 1
			b += 1
		if cont == nr:
			return [True,posx,posy,6]
		y = self._g.getBoard()
		a = 4
		b = 0
		cont = 0
		posx = 0
		posy = 0
		ant = 0
		for cnt in range(0,5):
			if y[a][b] == ant and y[a][b]:
				cont += 1
			else:
				cont -= 1
			ant = y[a][b]
			if cont == nr:
				posx = a
				posy = b
			a -= 1
			b += 1
		if cont == nr:
			return [True,posx,posy,6]

		return [False]

	def transmite(self, mat):
		self._g.trans(mat)

	def chooseRandom(self):
		'''
		the chaos chooses a random point, in range
		check if the move is valid, i.e., free space
		'''
		x = randint(0,5)
		y = randint(0,5)
		ok = 1
		while ok:
			try:
				self.checkMove(Point(x,y))
				self.addPoint(Point(x,y),0)
				ok = 0
			except Exception:
				pass
		return True

	def deSalvat(self):
		return self._g.getBoard()

	def getBoard(self):
		return self._g