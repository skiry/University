import math, copy


class Problem:
    def __init__(self, fileName):
        self.__fileName = fileName
        self.__finalState = []
        self.readFromFile()

    def readFromFile(self):
        file = open(self.__fileName, "r")
        self.__n = int(file.read(1))
        file.readline()

        self.__initialState = [[0] * self.__n for x in range(0, self.__n)]
        for i in range(0, self.__n):
            text = file.readline().split()
            for j in range(0, len(text)):
                self.__initialState[i][j] = int(text[j])
        print(self.__initialState)
        # self.expand(self.__initialState)

    def checkFinalState(self, state):
        neededSum = self.__n * (self.__n + 1) / 2
        for i in range(0, self.__n):
            lineSum = 0
            colSum = 0
            for j in range(0, self.__n):
                lineSum += state[i][j]
                colSum += state[j][i]
            if lineSum != neededSum or colSum != neededSum:
                return False

        quadrant = [0 for x in range(self.__n)]

        for i in range(0, self.__n):
            for j in range(0, self.__n):
                quadrant[
                    int(i / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)) + int(j / int(math.sqrt(self.__n)))] \
                    += state[i][j]
        for q in quadrant:
            if q != neededSum:
                return False

        self.__finalState = state
        return True

    def expand(self, state):
        result = []
        for i in range(0, len(state)):
            for j in range(0, len(state)):
                if state[i][j] == 0:
                    values = [i for i in range(0, len(state) + 1)]
                    for k in range(0, len(state)):
                        if state[i][k] != 0:
                            values[state[i][k]] = 0
                        if state[k][j] != 0:
                            values[state[k][j]] = 0

                    for k in range(int(i / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)),
                                   int(i / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)) + int(
                                       math.sqrt(self.__n))):
                        for l in range(int(j / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)),
                                   int(j / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)) + int(
                                       math.sqrt(self.__n))):
                            if state[k][l] != 0:
                                values[state[k][l]] = 0

                    atLeastOne = False

                    for k in values:
                        if k != 0:
                            newState = copy.deepcopy(state)
                            newState[i][j] = k
                            result.append(newState)
                            atLeastOne = True

                    if atLeastOne:
                        return result
                    return []
        return []

    def getInitialState(self):
        return self.__initialState

    def hasSolution(self):
        return self.__finalState != []

    def heuristic(self, state):
        finalScore = 0
        for i in range(0, len(state)):
            for j in range(0, len(state)):
                if state[i][j] == 0:
                    values = [i for i in range(0, len(state) + 1)]

                    for k in range(0, len(state)):
                        if state[i][k] != 0:
                            values[state[i][k]] = 0
                        if state[k][j] != 0:
                            values[state[k][j]] = 0

                    for k in range(int(i / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)),
                                   int(i / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)) + int(
                                       math.sqrt(self.__n))):
                        for l in range(int(j / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)),
                                   int(j / int(math.sqrt(self.__n))) * int(math.sqrt(self.__n)) + int(
                                       math.sqrt(self.__n))):
                            if state[k][l] != 0:
                                values[state[k][l]] = 0

                    for k in values:
                        if k != 0:
                            finalScore = finalScore + 1
        return finalScore

    def __str__(self):
        res = "----" * (len(self.__finalState)) + '\n' + " "
        for i in self.__finalState:
            isFirst = True
            for j in i:
                if isFirst == True:
                    isFirst = False
                else:
                    res += '| '
                res += str(j) + " "
            res += '\n' + "----" * (len(self.__finalState)) + '\n' + " "

        return res
