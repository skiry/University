n = 10
a = [2,5,-12,-4,2,1,-1,0,3,-2]
semn = [0 for x in range(n)]

def afis(semn, a, n, sum):
	text = ""
	for i in range(0, n):
		if semn[i] == 0:
			#print(" + ", end="")
			text += " + "
		elif semn[i] == 1:
			#print(" - ", end="")
			text += " - "
		#print(a[i], end="")
		text += str(a[i])
	#print(" = ", sum)
	text += " = " + str(sum) + '\n'

	f = open("rezultatI.txt", "a")
	f.write(text)
	f.close()
	
def isSolution(semn, a, n):
	sum = 0
	for i in range(0,n):
		if semn[i]:
			sum -= a[i]
		else:
			sum += a[i]
	if sum >= 0:
		return [True,sum]
	return [False]

def backt():
	global a, n
	index = 0
	semn[0] = -1
	while index > -1:
		Pass = True
		semn[index] += 1
		if semn[index] > 1:
			index -= 1
			Pass = False
		if Pass:
			if index == n - 1:
				x = isSolution(semn,a,n)
				if x[0]:
					afis(semn, a, n, x[1])
			else:
				index += 1
				semn[index] = -1

f = open("rezultatI.txt", "w")
f.write("")
f.close()
backt()