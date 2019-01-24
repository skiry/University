#mutation: swap method
#crossover: 2-cutting point crossover
import random
from Problem import Problem

class Individ:
    def __init__(self, length):
        '''
        :param length: the number of genes that one individ has
        '''
        random.seed()
        self.__length = length

    def createIndivid(self):
        '''
        randomly create an individ-randomly the genes-
        :return: the individ
        '''
        self.__visited = [0 for x in range(0, self.__length)]
        self.finalIndivid = [0 for x in range(0, self.__length)]
        self.__lastAdded = 0
        while self.__lastAdded != self.__length:
            r = random.randint(0, self.__length - 1)
            if self.__visited[r] == 0:
                self.finalIndivid[self.__lastAdded] = r
                self.__lastAdded = self.__lastAdded + 1
                self.__visited[r] = 1

        print("Generated the following individ:")
        print(self.finalIndivid)

        return self.finalIndivid

    def fitness(self, individ, problem):
        '''
        Generate the fitness of one individ calculating the size of the
        longest subsequence that is in increasing order
        :param individ: the individ - subject of the fitness function
        :param problem: the specific data for the problem
        :return:
        '''
        score = 0
        self.longest = [0 for x in range(0, self.__length)]
        for i in range(1, self.__length):
            if problem.lengths[individ[i]] >= problem.lengths[individ[i - 1]] and \
                    problem.colors[individ[i]] != problem.colors[individ[i - 1]]:
                self.longest[individ[i]] = self.longest[individ[i - 1]] + 1

        if sum(self.longest) != 0:
            '''
            if there are at least 2 consecutive OK cubes, add 1
            to the result because when we have a match it is
            considered as 1-length, when it should be 2
            '''
            return max(self.longest) + 1
        return max(self.longest)

    def mutate(self, individ, probability):
        '''
        Get 2 random positions and swap their values
        :param individ: the individual on which the mutation is being applied
        :param probability: probability of mutation
        :return: the individ w/ or w/out the mutation
        '''
        if random.random() < probability:
            r1 = random.randint(1, self.__length - 2)
            r2 = random.randint(1, self.__length - 2)
            while r1 == r2:
                r2 = random.randint(1, self.__length - 2)
            aux = individ[r1]
            individ[r1] = individ[r2]
            individ[r2] = aux

        return individ

    def crossover(self, father, mother, probability):
        '''
        Create the offsprings by getting 2 random positions and putting
        alternatively from father in the first one and from mother in
        the second one, and when getting to the first position, switch
        the parents from which the offspring inherits the genes
        :param father: the first individual
        :param mother: the second individual
        :param probability: probability of crossover
        :return: both offsprings
        '''
        if random.random() < probability:
            r1 = random.randint(1, self.__length - 2)
            r2 = random.randint(1, self.__length - 2)
            while r1 == r2:
                r2 = random.randint(1, self.__length - 2)
            result1 = [-1 for x in range(0, self.__length)]
            result2 = [-1 for x in range(0, self.__length)]
            for i in range(0, min(r1, r2)):
                result1[i] = father[i]
                result2[i] = mother[i]
            for i in range(max(r1, r2), self.__length):
                result1[i] = father[i]
                result2[i] = mother[i]
            for i in range(min(r1, r2), max(r1, r2)):
                put1 = 1
                put2 = 1
                for j in range(self.__length):
                    if mother[j] not in result1 and put1:
                        result1[i] = mother[j]
                        put1 = 0
                    if father[j] not in result2 and put2:
                        result2[i] = father[j]
                        put2 = 0

            return result1, result2
        return [], []
