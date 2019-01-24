import random

class Problem:
    def __init__(self, fileName):
        random.seed()
        self.mutationProb = 0.5
        self.crossOverProb = 0.5
        self.populationSize = 5
        self.numberOfIter = 100
        self.numberOfGenes = 5

        self.loadData(fileName)

    def loadData(self, fileName):
        self.inputData = []
        self.testData = []
        self.resultInput = []
        self.resultTest = []

        constantsNo = 3
        self.inputNo = 75
        counter = 0

        first = 1
        with open(fileName, "r") as openfileobject:
            for line in openfileobject:
                counter = counter + 1
                if first:
                    '''
                    avoid the description of the data
                    '''
                    first = 0
                elif counter < 75:
                    data = line.split(",")
                    currentData = []
                    for i in range(1, 10):
                        currentData.append(float(data[i]))
                    for i in range(0, constantsNo):
                        currentData.append(random.randint(1, 500))
                    self.inputData.append(currentData)
                    self.resultInput.append(float(data[10]))
                else:
                    data = line.split(",")
                    currentData = []
                    for i in range(1, 10):
                        currentData.append(float(data[i]))
                    for i in range(0, constantsNo):
                        currentData.append(random.randint(1, 500))
                    self.testData.append(currentData)
                    self.resultTest.append(float(data[10]))

        info = open("param.in", "r")
        self.mutationProb = float(info.readline().split(" ")[1])
        self.crossOverProb = float(info.readline().split(" ")[1])
        self.populationSize = int(info.readline().split(" ")[1])
        self.numberOfIter = int(info.readline().split(" ")[1])
