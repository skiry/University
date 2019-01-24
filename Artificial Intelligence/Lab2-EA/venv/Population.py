#selection: GENITOR
from Individ import Individ

class Population:
    def __init__(self, length, genes):
        '''
        Creates @length individs, each with @genes genes
        :param length: number of individs of the population
        :param genes: number of genes of one individ
        '''
        self.individ = Individ(genes)
        self.noIndivids = length
        self.individs = []
        for i in range(0, self.noIndivids):
            self.individs.append(self.individ.createIndivid())

    def selection(self, population, offspring1, offspring2, problem):
        '''
        Make a steady-state selection. Exclude the worst individual
        and put the best of the offsprings in the population
        :param population: the population with all the individuals
        :param offspring1: the first child
        :param offspring2: the second child
        :param problem: the main info to be evaluated
        :return: the new population
        '''
        bestIndivid = [(self.individ.fitness(x, problem), x) for x in self.individs]
        bestIndivid = sorted(bestIndivid)

        if max(self.individ.fitness(offspring1, problem), self.individ.fitness(offspring2, problem)) > \
            self.individ.fitness(bestIndivid[0][1], problem):
            newPopulation = [bestIndivid[x][1] for x in range(1, len(bestIndivid))]
            if self.individ.fitness(offspring1, problem) >\
                self.individ.fitness(offspring2, problem):
                newPopulation.append(offspring1)
            else:
                newPopulation.append(offspring2)
            population.changeIndivids(newPopulation)

        return population

    def evaluate(self, population, problem):
        '''
        Evaluate a population
        :param population: the population being evaluated
        :param problem: the data which is being evaluated(specific info)
        '''
        bestIndivid = [(self.individ.fitness(x, problem), x) for x in self.individs]
        bestIndivid = sorted(bestIndivid)

        result = bestIndivid[len(bestIndivid) - 1]
        print('Result: The longest sequence has %3.2f consecutive elements and its part of the '
              'following individual' % \
              (result[0]))

        for x in bestIndivid:
            print("fit:", x[0], "; val: ", x[1])
        for i in range(len(result[1])):
            print("Cube with size ", problem.lengths[result[1][i]],
                  " has color ", problem.colors[result[1][i]])

        return
    def changeIndivids(self, newIndivids):
        '''
        Assign new individuals to a population
        :param newIndivids: new individuals to be assigned
        '''
        self.individs = newIndivids

    def getAllFitness(self, problem):
        fitnessAll = []
        for i in self.individs:
            fitnessAll.append(self.individ.fitness(i, problem))

        return fitnessAll

    def getBest(self, population, problem):
        '''
        Evaluate a population
        :param population: the population being evaluated
        :param problem: the data which is being evaluated(specific info)
        '''
        bestIndivid = [(self.individ.fitness(x, problem), x) for x in self.individs]
        bestIndivid = sorted(bestIndivid)

        return bestIndivid[len(bestIndivid) - 1]