class repoReservations:
	def __init__(self):
		self._data = {}

	def addRsv(self, reserv):
		'''
		add a reservation
		'''
		room = reserv.getRN()
		name = reserv.getNM()
		guests = reserv.getNG()
		ad = reserv.getAD()
		dd = reserv.getDD()
		self._data[reserv.getNO()] = [room,name,guests,ad,dd]

	def delRsv(self, id):
		'''
		delete a reservation
		'''
		del self._data[id]

	def getAll(self):
		return self._data

class repoRooms:
	def __init__(self):
		self._rooms = {}
		self.one = 0
		self.two = 0
		self.four = 0
	
	def addRoom(self, room):
		'''
		add a room
		'''
		t = room.getTYPE()
		if int(t) == 1:
			self.one += 1
		elif int(t) == 2:
			self.two += 1
		else:
			self.four += 1
		self._rooms[int(room.getID())] = int(room.getTYPE())

	def getAll(self):
		return self._rooms