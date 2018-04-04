n = 10
a = [2,5,-12,-4,2,1,-1,0,3,-2]
semn = [0 for x in range(n)]

def backt(list, index, sum, semn, sign = 0):
	if sign == 0:
		sum += list[index]
		semn[index] = 0
	elif sign == 1:
		sum -= list[index]
		semn[index] = 1

	if index == n - 1:
		if sum >= 0:
			yield semn,sum

	elif index < n:
		yield from backt(list, index + 1, sum, semn, 0)
		yield from backt(list, index + 1, sum, semn, 1)

	if sign == 0:
		sum -= list[index]
	elif sign == 1:
		sum += list[index]

s = 0
text = ""
for j in range(0,2):
	for x in backt(a, 0, s, semn, j):
		for i in range(0,n):
			if x[0][i]:
				#print(" - ", end='')
				text += " - "
			else:
				#print(" + ", end='')
				text += " + "
			#print(a[i], end='')
			text += str(a[i])
		#print(" = ", x[1],  end='')
		text += " = "
		text += str(x[1]) + '\n'
		#print('\n')
f = open("rezultatR.txt", "w")
f.write(text)
f.close()