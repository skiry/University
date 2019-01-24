#selection: GENITOR
from Chromosome import Chromosome

class Population:
    def __init__(self, length):
        '''
        Creates @length Chromosomes, each with random number of genes
        :param length: number of Chromosomes of the population
        '''
        self.Chromosome = Chromosome()
        self.noChromosomes = length
        self.Chromosomes = []
        for i in range(0, self.noChromosomes):
            myChromosome = Chromosome()
            myChromosome.growExpression(0)
            self.Chromosomes.append(myChromosome)

    def selection(self, population, offspring1, problem):
        '''
        Take 32% - best of them, then take 80% of them
        Take 68% of all, randomly, and take 90% of them
        :param population: the population with all the Chromosomes
        :param offspring1: the child
        :param problem: the main info to be evaluated
        :return: the new population
        '''
        bestChromosome = [(x.computeFitness(problem.inputData, problem.resultInput, problem.inputNo), x)
                          for x in self.Chromosomes]
        bestChromosome = sorted(bestChromosome)

        newPopulation = [bestChromosome[x][1] for x in range(0, len(bestChromosome))]
        newPopulation.append(offspring1)

        return newPopulation

    def evaluate(self, population, problem):
        '''
        Evaluate a population
        :param population: the population being evaluated
        :param problem: the data which is being evaluated(specific info)
        '''
        bestChromosome = [(x.computeFitness(problem.inputData, problem.resultInput, problem.inputNo), x)
                          for x in self.Chromosomes]
        bestChromosome = sorted(bestChromosome)

        result = bestChromosome[0]
        print()
        print("Result: The regression with fitness ",result[0]," is obtained by the following expression")
        result[1].printInorder(0)
        print()

        for x in bestChromosome:
            print("fit:", x[0], "; val: ", x[1])
            x[1].printInorder(0)
            print()

        return
    def changeChromosomes(self, newChromosomes):
        '''
        Assign new Chromosoms to a population
        :param newChromosomes: new Chromosoms to be assigned
        '''
        self.Chromosomes = newChromosomes

    def getAllFitness(self, problem):
        fitnessAll = []
        for i in self.Chromosomes:
            fitnessAll.append(self.Chromosome.computeFitness(problem.inputData, problem.resultInput, problem.inputNo))

        return fitnessAll

    def getBest(self, population, problem):
        '''
        Evaluate a population
        :param population: the population being evaluated
        :param problem: the data which is being evaluated(specific info)
        '''
        bestChromosome = [(x.computeFitness(problem.inputData, problem.resultInput, problem.inputNo), x)
                          for x in self.Chromosomes]
        bestChromosome = sorted(bestChromosome)

        return bestChromosome[0]