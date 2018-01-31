bases = 0
def backt(poz, val, index, n):
    if index == n:
        yes = gauss(generateMatrix(poz))
        if yes:
            global bases
            bases += 1
            print(poz)
    else:
        for i in val:
            if val[i] == 0:
                poz[index] = i
                val[i] = 1
                backt(poz, val, index + 1, n)
                val[i] = 0
                poz[index] = 0

def main():
    try:
        try:
            n = int(input("Insert n: "))
        except Exception:
            raise Exception("Natural number please!")
        poz = {}
        for i in range(0, n):
            poz[i] = 0
        val = {}
        for i in range(1, 2**n):
            val[i] = 0
        backt(poz, val, 0, n)
        print("Number of bases : ", bases)
    except Exception as exc:
        print(exc)

def generateMatrix(dict):
        matrix = {} 
        for i in range(0,len(dict)):
                # dict[i] = number
                for x in range(len(dict) -1 , -1, -1):
                        # x-position of every bit
                        res = 2**x
                        if dict[i]&res == res:
                                if i not in matrix:
                                        matrix[i] = [(1)]
                                else:
                                        matrix[i].append(1)
                        else:
                                if i not in matrix:
                                        matrix[i] = [(0)]
                                else:
                                        matrix[i].append(0)
        return matrix

def gauss(matrix):
        print(matrix)
        ok = 0
        zeros = {}
        if matrix[0][0] == 0:
                ok = 2
                for x in matrix:
                        if x and matrix[x][0] and ok != 1:
                                matrix[0], matrix[x] = matrix[x], matrix[0]
                                ok = 1
        if ok == 2:
            return False
        for counter in range(0,len(matrix)-1):
            add = {}
            for x in range(counter + 1,len(matrix)):
                    one, ctr = 1, 0
                    if matrix[x][counter] and matrix[counter][counter]:
                            value = matrix[x][counter] // matrix[counter][counter]
                            for i in range(0,len(matrix)):
                                    matrix[x][i] -= value * matrix[counter][i]
                                    if matrix[x][i] == 0 or matrix[x][i] == 2 or matrix[x][i] == -2:
                                        if one:
                                            ctr += 1
                                    else:
                                        one = 0
                            if x < ctr and ctr not in add:
                                add[x] = ctr
            sum = 0
            for j in range(0,len(matrix)):
                    if matrix[x][j] == 0 or matrix[x][j] == 2 or matrix[x][j] == -2:
                            sum += 1
            if sum == len(matrix):
                    return False
            for counter in add:
                try:
                    matrix[add[counter]], matrix[counter] = matrix[counter], matrix[add[counter]]
                except Exception:
                    pass

        #print("Edited",matrix)
        for counter in range(1,len(matrix)):
            res = 0
            for j in range(0,len(matrix)):
                if matrix[counter][j] == 0 or matrix[counter][j] == 2 or matrix[x][j] == -2:
                    res += 1
                else:
                    break
            zeros[counter] = res
        for ctr in range(1,len(zeros)):
            for ctr2 in range(ctr + 1,len(zeros) + 1):
                if zeros[ctr] == zeros[ctr2]:
                    return False
        return True
main()
