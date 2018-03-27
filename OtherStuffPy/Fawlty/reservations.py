class Reservation:
	def __init__(self, no, rn, nm, ng, ad, dd):
		'''
		reservation class
		no - unique number
		rn - room number
		nm - family name
		ng - number of guests
		ad - arrival date
		dd - departure date
		'''
		self._no = no
		self._rn = rn
		self._nm = nm
		self._ng = ng
		self._ad = ad
		self._dd = dd

	def getNO(self):
		return self._no

	def getRN(self):
		return self._rn

	def getNM(self):
		return self._nm

	def getNG(self):
		return self._ng

	def getAD(self):
		return self._ad

	def getDD(self):
		return self._dd

class Room:
	def __init__(self, id, type):
		'''
		a room
		id - room's id
		type - room's type : 1 - single, 2 - double, 3 - family
		'''
		self._id = id
		self._type = type

	def getID(self):
		return self._id

	def getTYPE(self):
		return self._type