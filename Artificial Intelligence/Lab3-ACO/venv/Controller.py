from Problem import Problem
from Ant import Ant

class Controller:
    def __init__(self):
        '''
        Load the parameters from the problem
        Create the trace matrix with (word, (x, y)) tuples
        word - word ID
        x - the x starting coordinate
        y - the y starting coordinate
        '''
        self.loadParameters()

        self.trace = dict()
        for i in range(self.p.numberOfWords):
            for j in self.p.beginPositions:
                self.trace[(i,j)] = 1

        self.fitnesses = []
        self.bestSol = []

    def run(self):
        '''
        Run @numberofIter iterations, select the best out of them
        :return: the best solution
        '''
        sol = []
        for i in range(self.p.numberOfIter):
            sol, ant = self.iteration()
            self.fitnesses.append(ant.fitness())

            if len(sol) > len(self.bestSol):
                self.bestSol = sol.copy()

        return self.bestSol, ant

    def iteration(self):
        '''
        Create @numberOfAnts ants in population, make moves as long as it is
        possible, update the pheromones
        :return: the current solution, best one of this iteration
        '''
        self.ants = [Ant(self.p.n, self.p.m, self.p.words,
                               self.p.beginPositions, self.p.lengths,
                               self.p.directions)
                           for x in range(self.p.numberOfAnts)]

        for i in range(self.p.numberOfWords):
            for ant in self.ants:
                ant.addMove(self.p.q0, self.trace, self.p.alpha, self.p.beta)
        #print("CTRL TRACE", self.trace)
        dTrace = [1.0 / self.ants[i].fitness() for i in range(len(self.ants))]
        for i in range(self.p.numberOfWords):
            for j in self.p.beginPositions:
                self.trace[(i, j)] = (1 - self.p.rho) * self.trace[(i, j)]

        for i in range(len(self.ants)):
            for j in self.ants[i].path:
                self.trace[j] = self.trace[j] + dTrace[i]

        currentBest = [ [self.ants[i].fitness(), i] for i in range(len(self.ants))]
        currentBest = max(currentBest)

        return self.ants[currentBest[1]].path, self.ants[currentBest[1]]

    def loadParameters(self):
        '''
        Create a wrapper for the main info of the problem
        '''
        self.p = Problem("data01.in")

    def printAntPath(self, ant):
        ant.printSolution()

    def getAllFitness(self):
        return self.fitnesses