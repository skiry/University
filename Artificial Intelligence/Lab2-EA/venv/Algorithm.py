import random
from Problem import Problem
from Population import Population

from Individ import Individ

class Algorithm:
    def __init__(self, fileName):
        '''
        Sets the base attributes and runs the iterations
        :param fileName: the file which has infos about probabilities and sizes
        '''
        self.problem = Problem(fileName)
        self.population = Population(self.problem.populationSize, self.problem.numberOfGenes)

    def iteration(self, population):
        '''
        One iteration
        :param population: the whole population
        '''
        r1 = random.randint(0, self.problem.populationSize - 1)
        r2 = random.randint(0, self.problem.populationSize - 1)
        if r1 != r2:
            c1, c2 = self.population.individ.crossover(population.individs[r1],
                                             population.individs[r2],
                                             self.problem.crossOverProb)
            if c1 != []:
                c1 = self.population.individ.mutate(c1, self.problem.mutationProb)
                c2 = self.population.individ.mutate(c2, self.problem.mutationProb)
                population = self.population.selection(population, c1, c2, self.problem)
        return population

    def run(self):
        for i in range(self.problem.numberOfIter):
            self.population = self.iteration(self.population)

        return self.population, self.problem

    def getAllFitness(self):
        return self.population.getAllFitness(self.problem)