from reservations import *
from repo import *
from random import randint
from datetime import date

class ctrlReservations:
	def __init__(self, repo, rms):
		self._repo = repo
		self._rms = rms

	def addReserv(self, r):
		'''
		parameters verification
		'''
		try:
			x = int(r.getNO())
			allOf = self._repo.getAll()
			if x in allOf:
				'''
				id must be unique
				'''
				raise ValueError("Room ID must be unique")
			y = int(r.getRN())
			if y not in range(1,11):
				'''
				room no must be bet 1 and 10
				'''
				raise ValueError("Room is must be between 1 and 10")
			z = r.getNM()
			if z == '':
				'''
				name not empty
				'''
				raise ValueError("Name is empty!")
			g = int(r.getNG())
			if g not in range(1,5):
				'''
				1 <= no. of guests <= 4
				'''
				raise ValueError("Less than 1 or more than 4 guests")

			date1 = r.getAD()
			date1 = date1.split('.')
			zi = int(date1[0])
			luna = int(date1[1])
			if zi not in range(1,32) or luna not in range(1,13):
				raise ValueError("Invalid arrival date")

			date2 = r.getDD()
			date2 = date2.split('.')
			zi1 = int(date2[0])
			luna1 = int(date2[1])
			if zi1 not in range(1,32) or luna1 not in range(1,13):
				raise ValueError("Invalid departure date")

			reserv = Reservation(x,y,z,g,r.getAD(),r.getDD())
			self._repo.addRsv(reserv)
		except Exception as exc:
			raise ValueError(exc)

	def checkRsv(self, r):
		'''
		check if the reservation has good parameters
		'''
		z = r[0]
		if z == '':
			'''
			name not empty
			'''
			raise ValueError("Name is empty!")
		try:
			if int(r[2]) not in range(1,5):
				raise ValueError("Less than 1 or more than 5 guests")

			date1 = r[3]
			date1 = date1.split('.')
			zi = int(date1[0])
			luna = int(date1[1])
			if zi not in range(1,32) or luna not in range(1,13):
				raise ValueError("Invalid arrival date")

			date2 = r[4]
			date2 = date2.split('.')
			zi1 = int(date2[0])
			luna1 = int(date2[1])
			if zi1 not in range(1,32) or luna1 not in range(1,13):
				raise ValueError("Invalid departure date")
			return True
		except Exception as exc:
			raise ValueError(exc)

	def createNo(self):
		'''
		random 4 digit number - unique id
		'''
		randomNo = randint(1000,9999)
		while randomNo in self.getAll():
			randomNo = randint(1000,9999)

		return randomNo	

	def findRoom(self, free, type, inc, sf):
		'''
		search for free rooms in period inc-sf
		'''
		ol = self._rms.getAll()
		reservatii = self.getAll()
		data1 = date(2019,int(inc[3]+inc[4]),int(inc[0]+inc[1]))
		data2 = date(2019,int(sf[3]+sf[4]),int(sf[0]+sf[1]))
		for r in reservatii:
			one = reservatii[r]
			inceput = date(2019,int(one[3][3]+one[3][4]),int(one[3][0]+one[3][1]))
			sfarsit = date(2019,int(one[4][3]+one[4][4]),int(one[4][0]+one[4][1]))
			#print(inceput,sfarsit,data1,data2)
			if (sfarsit > data1 and sfarsit < data2) or (inceput < data2 and inceput > data1) or (data1 > inceput and data1 < sfarsit) or (data2 > inceput and data2 < sfarsit):
				ol = self._rms.getAll()
				for x in ol:
					if x == one[0]:
						if ol[x] == int(type):
							free = free - 1
			else:
				ol = self._rms.getAll()
				for x in ol:
					if x == one[0]:
						if ol[x] == int(type):
							free = free - 1
		return lista

	def checkFree(self, inc, sf):
		'''
		check for free rooms in period ad-dd
		'''
		lista = {}
		ol = self._rms.getAll()
		for x in ol:
			lista[x] = ol[x]
		reservatii = self.getAll()
		data1 = date(2019,int(inc[3]+inc[4]),int(inc[0]+inc[1]))
		data2 = date(2019,int(sf[3]+sf[4]),int(sf[0]+sf[1]))
		for r in reservatii:
			one = reservatii[r]
			inceput = date(2019,int(one[3][3]+one[3][4]), (one[3][0]+one[3][1]))
			sfarsit = date(2019,int(one[4][3]+one[4][4]),int(one[4][0]+one[4][1]))
			#print(inceput,sfarsit,data1,data2)
			if (sfarsit > data1 and sfarsit < data2) or (inceput < data2 and inceput > data1) or (data1 > inceput and data1 < sfarsit) or (data2 > inceput and data2 < sfarsit):
				del lista[one[0]]
		return lista

	def sortMonths(self):
		luni = {}
		for x in range(1,13):
			luni[x] = 0
		lista = []
		nume = []
		reservatii = self.getAll()
		for r in reservatii:
			one = reservatii[r]
			luna1 = int(one[3][3]+one[3][4])
			zi1 = int(one[3][0]+one[3][1])
			luna2 = int(one[4][3]+one[4][4])
			zi2 = int(one[4][0]+one[4][1])
			if luna2>luna1:
				for i in range(zi1,30):
					luni[luna1] += 1
				for i in range(1,zi2):
					luni[luna2] += 1
			else:
				for i in range(zi1,zi2):
					luni[luna1] += 1
		for x in luni:
			lista.append(luni[x])
			nume.append(x)
		for i in range(0,len(lista)-1):
			for j in range(i+1,len(lista)):
				if lista[i] < lista[j]:
					lista[i],lista[j] = lista[j],lista[1]
					nume[i],nume[j]=nume[j],nume[j]
		return (lista,nume)


	def delRsv(self, id):
		'''
		check if id is valid and if it is, delete id
		'''
		if id not in self.getAll():
			raise ValueError("id not valid")
		else:
			self._repo.delRsv(id)


	def getAll(self):
		return self._repo.getAll()

class ctrlRooms:
	def __init__(self, repo):
		self._repo = repo

	def addRoom(self, room):
		try:
			x = int(room.getID())
			if x not in range(1,11):
				raise ValueError("Room must be between 1 and 10")
			y = int(room.getTYPE())
			if y not in range(1,4):
				raise ValueError("Room type must be 1, 2 or 3")
			self._repo.addRoom(room)
		except Exception as exc:
			raise ValueError(exc)

	def getAll(self):
		return self._repo.getAll()