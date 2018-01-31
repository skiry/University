from repo import *
from ctrl import *
from main import *

class UI:
	'''
	docstring for UI
	'''
	def __init__(self, game):
		'''
		initialization of the game
		'''
		self._game = game
		self.ships()
	
	def ships(self):
		'''
		the player adds ships till he starts the game
		'''
		putShips = 1
		counter = 0
		while putShips:
			x = input("Place a ship: ")
			x = x.split(' ')
			if x[0] == "ship":
				x[1].strip()
				try:
					ok = self._game.validate(x[1])
					if ok:
						self._game.addShip(x[1])
						counter += 1
				except Exception as exc:
					print(exc)
					print("The ship is out of the board or there is an overlapping!")
			elif x[0] == "start":
				if counter > 1:
					putShips = 0
				else: 
					print("Not enough ships!")
			print(self._game.getBoard())
		self.start()

	def start(self):
		'''
		the game itself
		'''
		self._game.AIships()
		playing = True
		player = 0
		user = 0
		whoseTurn = 0
		while playing:
			try:
				if whoseTurn == 0:
					atack = input("Your turn: ")
					atack = atack.split(' ')
					if atack[0] == "atack":
						atack[1].strip()
						try:
							ok = self._game.checkMove(atack[1])
							self._game.makeMove(atack[1])
						except Exception:
							raise Exception("Make a valid move!")
						whoseTurn = 1
					elif atack[0] == "cheats":
						self._game._board._cheats = 1
				else:
					self._game.AImove()
					whoseTurn = 0
				if self._game._board._gasitePl == 6 or self._game._board._gasiteAI == 6:
					playing = False
				print(self._game.getBoard())
			except Exception as exc:
				print(exc)

			
board = Repository()
game = Controller(board)
ui = UI(game)