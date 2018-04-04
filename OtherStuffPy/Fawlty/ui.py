from reservations import *
from repo import *
from ctrl import *

class UI:
	def __init__(self, room, reserv):
		self._rsv = reserv
		self._room = room
		self.readFiles()

	def readFiles(self):
		'''
		read the rooms and the reservations from files
		'''
		f = open("rooms.txt","r")
		txt = f.read().split('\n')
		for x in txt:
			if len(x) > 1:
				y = x.split(';')
				try:
					self._room.addRoom(Room(y[0],y[1]))
				except ValueError as exc:
					print(exc)
		f.close()

		f = open("reservations.txt","r")
		txt = f.read().split('\n')
		for x in txt:
			if len(x) > 1:
				y = x.split(',')
				try:
					self._rsv.addReserv(Reservation(y[0],y[1],y[2],y[3],y[4],y[5]))
				except ValueError as exc:
					print(exc)
		f.close()

		self.start()

	def start(self):
		menu = '''
				  1. Make reservation
				  2. Delete reservation
				  3. Show available rooms
				  4. Monthly report
				  5. Day of week report
				  6. Show reservations
				  7. Exit
				  '''
		ok = True
		while ok:
			print(menu)
			try:
				cmd = int(input("Enter command: "))
				if cmd not in range(1,8):
					raise ValueError("Invalid command!")
				if cmd == 7:
					text = ""
					y = self._rsv.getAll()
					f = open("reservations.txt","w")
					for x in y:
						text += str(x) + "," + str(y[x][0]) + "," + str(y[x][1]) + "," + str(y[x][2]) + "," + str(y[x][3])
						text += '\n'
					f.write(text)
					f.close()
					break
				elif cmd == 1:
					r = self.makeReservation()
					if self._rsv.checkRsv(r):
						number = self._rsv.createNo()
						unu = self._room._repo.one
						doi = self._room._repo.two
						trei = self._room._repo.four
						if r[1] == "1":
							chooseRoom = self._rsv.findRoom(unu,1,r[3],r[4])
						elif r[1] == "2":
							chooseRoom = self._rsv.findRoom(doi,2,r[3],r[4])
						else:
							chooseRoom = self._rsv.findRoom(trei,3,r[3],r[4])
						if chooseRoom == False:
							raise ValueError("No free rooms!")
						else:
							self._rsv.addReserv(Reservation(number,chooseRoom,r[0],r[2],r[3],r[4]))
				elif cmd == 6:
					y = self._rsv.getAll()
					for x in y:
						print(x,y[x])
				elif cmd == 2:
					try:
						id = int(input("Reservation id: "))
						self._rsv.delRsv(id)
					except Exception as exc:
						raise ValueError(exc)
				elif cmd == 3:
					ad = input("Arrival date <day.month>: ")
					dd = input("Departure date <day.month>: ")
					lista = self._rsv.checkFree(ad,dd)
					if len(lista):
						for x in lista:
							print("Room number ",x," of type ",lista[x])
				elif cmd == 4:
					rep = self._rsv.sortMonths()
					for x in range(1,12):
						if rep[0][x]:
							print("Month", rep[1][x]," busy ",rep[0][x])
			except Exception as exc:
				print(exc)

	def makeReservation(self):
		nm = input("Family name: ")
		rt = input("Room type: ")
		ng = input("No of guests: ")
		ad = input("Arrival date <day.month>: ")
		dd = input("Departure date <day.month>: ")
		return (nm,rt,ng,ad,dd)
		


repoRsv = repoReservations()
repoRoom = repoRooms()
ctrlRsv = ctrlReservations(repoRsv,repoRoom)


ctrlRoom = ctrlRooms(repoRoom)

ui = UI(ctrlRoom, ctrlRsv)
