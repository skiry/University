class Problem:
    def __init__(self, fileName):
        self.mutationProb = 0.5
        self.crossOverProb = 0.5
        self.populationSize = 5
        self.numberOfIter = 100
        self.numberOfGenes = 5

        self.loadData(fileName)

    def loadData(self, fileName):
        data = open(fileName, "r")
        self.numberOfGenes = int(data.readline())

        self.lengths = data.readline().split(" ")
        for i in range(0,len(self.lengths)):
            self.lengths[i] = int(self.lengths[i])

        self.colors = data.readline().split(" ")
        for i in range(0, len(self.colors)):
            self.colors[i] = int(self.colors[i])

        if len(self.colors) != len(self.lengths) or len(self.colors) != self.numberOfGenes:
            raise Exception("Different lengths on side-lengths and cube colors and/or no. of genes.")

        info = open("param.in", "r")
        self.mutationProb = float(info.readline().split(" ")[1])
        self.crossOverProb = float(info.readline().split(" ")[1])
        self.populationSize = int(info.readline().split(" ")[1])
        self.numberOfIter = int(info.readline().split(" ")[1])
