from point import *
from repo import *
from ctrl import *
class UI:
	def __init__(self, game):
		self._game = game
		self.start()

	def start(self):
		choose = '''
		1. Load an existing game
		2. New game
		'''
		ok = 1
		while ok:
			try:
				try:
					x = int(input(choose))
					if x not in range(1,3):
						raise ValueError("Not ok")
				except Exception as exc:
					raise Exception(exc)
					ok = 0
				if x == 2:
					self.newGame()
				else:
					self.loadGame()
			except Exception as exc:
				print(exc)

	def newGame(self):
		ok = 1
		player = 1
		while ok:
			try:
				if self._game._g.no == 36:
					ok = 0
					raise ValueError("Game over. Chaos wins")
				if self._game.checkWin(4)[0] == True:
					ok = 0
					raise ValueError("Game over. Order wins")
				if player:
					print(self._game.getBoard())
					x = input("Do you want X or O?") 
					try:
						if x.lower() == 'x' or x.lower() == 'o':
							if x.lower() == 'x':
								self._game._g.player = 1
							else:
								self._game._g.player = 2
						else:
							raise ValueError("X or O !!!")
						a = input("First coordinate :")
						if a == "save":
							self.saveGame()
							raise Exception("Game saved. Still playing the game ...")
						elif a == "exit":
							ok = 0
							raise Exception("Game finished")
						b = int(input("Second coordinate :"))
						a = int(a)
						self._game.checkMove(Point(a,b))
						self._game.addPoint(Point(a,b),player)
						player = 0
						print(self._game.getBoard())
					except Exception as exc:
						raise ValueError(exc)
				else:
					if self._game.block() == False:
						self._game.chooseRandom()
					player = 1
			except Exception as exc:
				print(exc)

	'''
	def continueGame(self):
		player = 1
		ok = 1
		while ok:
			try:
				print(self._game.getBoard())
				if player:
					try:
						a = input("First coordinate :")
						if a == "save":
							self.saveGame()
							raise Exception("Game saved. Still playing the game ...")
						elif a == "exit":
							ok = 0
							raise Exception("Game finished")
						b = int(input("Second coordinate :"))
						a = int(a)
						self._game.checkMove(Point(a,b))
						self._game.addPoint(Point(a,b),player)
						player = 0
					except Exception as exc:
						raise ValueError(exc)
				else:
					if self._game.block() == False:
						self._game.chooseRandom()
					player = 1
			except Exception as exc:
				print(exc)
		'''

	def saveGame(self):
		f = open("game.txt","w")
		txt = ""
		txt += str(self._game._g.player)
		txt += '\n'
		y = self._game.deSalvat()
		for x in y:
			for j in x:
				txt += str(j)
			txt += '\n'
		f.write(txt)
		f.close()

	def loadGame(self):
		f = open("game.txt","r")
		t = f.read().split('\n')
		integer = 0
		mat = [[0 for x in range(6)] for y in range(7)]
		for x in t:
			if x!= '':
				if integer == 0:
					self._game._g.player = int(x[0])
				else:
					for j in range(0,6):
						mat[integer][j] = int(x[j])
				integer += 1
		self._game.transmite(mat)
		self.newGame()
		f.close()

repo = Board()
game = Game(repo)
ui = UI(game)