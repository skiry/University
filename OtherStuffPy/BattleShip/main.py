class Point:
	"""'''
	a Point object
	'''"""
	def __init__(self, x, y, z, t, q, r):
		self._l1 = x
		self._c1 = y
		self._l2 = z
		self._c2 = t
		self._l3 = q
		self._c3 = r

	def getL1(self):
		'''
		X coordinate getter
		'''
		return self._l1
	
	def getC1(self):
		'''
		Y coordinate getter
		'''
		return self._c1

	def getL2(self):
		'''
		X coordinate getter
		'''
		return self._l2
	
	def getC2(self):
		'''
		Y coordinate getter
		'''
		return self._c2
	
	def getL3(self):
		'''
		X coordinate getter
		'''
		return self._l3
	
	def getC3(self):
		'''
		Y coordinate getter
		'''
		return self._c3