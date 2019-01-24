import random
from Problem import Problem
from Population import Population

from Chromosome import Chromosome

class Algorithm:
    def __init__(self, fileName):
        '''
        Sets the base attributes and runs the iterations
        :param fileName: the file which has infos about probabilities and sizes
        '''
        self.problem = Problem(fileName)
        self.population = Population(self.problem.populationSize)

    def iteration(self, population, i):
        '''
        One iteration
        :param population: the whole population
        '''
        r1 = random.randint(0, self.problem.populationSize - 1)
        r2 = random.randint(0, self.problem.populationSize - 1)
        if r1 != r2:
            c1 = self.population.Chromosome.crossover(population.Chromosomes[r1],
                                             population.Chromosomes[r2],
                                             self.problem.crossOverProb)
            if c1 != []:
                c1 = self.population.Chromosome.mutate(c1, self.problem.mutationProb)
                population = self.population.selection(population, c1, self.problem)
                #80% + 20%

        for x in population.Chromosomes:
            print("Chromosomes after an iteration")
            x.printInorder(0)
            print()
        return population

    def run(self):
        print("Running algorithm")
        for i in range(self.problem.numberOfIter):
            self.population = self.iteration(self.population, i)

        return self.population, self.problem

    def getAllFitness(self):
        return self.population.getAllFitness(self.problem)