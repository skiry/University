class Problem:
    def __init__(self, fileName):
        self.loadData(fileName)

    def loadData(self, fileName):
        '''
        Get the data regarding the requirement and also the main parameters
        :param fileName: file data name
        '''
        data = open(fileName, "r")

        self.numberOfWords = int(data.readline())
        self.words = [data.readline().strip() for x in range(self.numberOfWords)]

        self.beginPositions = []
        self.lengths = []
        self.directions = []

        self.n, self.m = map(int, data.readline().split(" "))
        for i in range(self.numberOfWords):
            line = data.readline().split(" ")
            self.beginPositions.append((int(line[0]), int(line[1])))
            self.directions.append(line[2])
            self.lengths.append(int(line[3]))

        info = open("param.in", "r")
        self.alpha = float(info.readline().split(" ")[1])
        self.beta = float(info.readline().split(" ")[1])
        self.rho = float(info.readline().split(" ")[1])
        self.q0 = float(info.readline().split(" ")[1])
        self.numberOfAnts = int(info.readline().split(" ")[1])
        self.numberOfIter = int(info.readline().split(" ")[1])
