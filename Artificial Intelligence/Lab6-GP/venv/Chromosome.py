'''
Some specific functions for a GP variation
'''

import random
import math

DEPTH_MAX = 6
terminals = ['Cement','Slag','FlyAsh','Water','SP','CoarseAggr','FineAggr','Slump', 'Flow', 'c1', 'c2', 'c3']
noTerminals = len(terminals)
functions = ['+','-','*']
noFunctions = len(functions)

class Chromosome:
    def __init__(self, d = DEPTH_MAX):
        random.seed()
        self.mDepth = random.randint(3, d)
        self.repres = [0 for i in range(2 ** (self.mDepth) - 1 )]
        self.fitness = 0
        self.size = 0

    def growExpression(self, pos = 0, mustBeFunc = 1):
        """
        initialise randomly an expression
        """
        if pos >= len(self.repres):
            return
        if pos < (2 ** (self.mDepth - 1) - 1):
            if random.random() < 0.5 or pos == 0 or mustBeFunc:
                self.repres[pos] = -random.randint(1, noFunctions)
            else:
                #self.repres[pos] = random.randint(1, noTerminals)
                self.repres[pos] = -random.randint(1, noFunctions)
        else:
            self.repres[pos] = random.randint(1, noTerminals)

        if self.repres[pos] > 0 or (pos >= (2 ** (self.mDepth - 3) - 1) and pos < (2 ** (self.mDepth - 2) - 1)):
            mustBeFunc = 1
        else:
            mustBeFunc = 0
        self.growExpression((pos << 1) + 1, mustBeFunc)
        self.growExpression((pos << 1) + 2, mustBeFunc)

    def evalExpression(self, pos, crtData):
        """
        the expresion value for some specific terminals
        """
        if pos >= len(self.repres):
            return
        if  self.repres[pos] > 0: # a terminal
            return crtData[self.repres[pos] - 1], crtData
        elif self.repres[pos] < 0:  # a function
            if functions[-self.repres[pos] - 1] == '+':
                auxFirst = self.evalExpression((pos << 1) + 1, crtData)
                auxSecond = self.evalExpression((pos << 1) + 2, crtData)
                return auxFirst[0] + auxSecond[0], crtData
            elif functions[-self.repres[pos] - 1] == '-':
                auxFirst = self.evalExpression((pos << 1) + 1, crtData)
                auxSecond = self.evalExpression((pos << 1) + 2, crtData)
                return auxFirst[0] - auxSecond[0], crtData
            elif functions[-self.repres[pos] - 1] == '*':
                auxFirst = self.evalExpression((pos << 1) + 1, crtData)
                auxSecond = self.evalExpression((pos << 1) + 2, crtData)
                return auxFirst[0] * auxSecond[0], crtData

    def computeFitness(self, crtData, crtOut, noExamples):
        '''
        the fitness function
        '''
        err = 0.0
        for i in range(noExamples - 2):
            err += abs(crtOut[i] - self.evalExpression(0, crtData[i])[0])
            #print("ERR",err)
            #print("ABS",abs(crtOut[i] - self.evalExpression(0, crtData[i])[0]))#
        self.fitness = err
        return self.fitness

    def crossover(self, off1, off2, prob):
        '''
        The trees are full. Our way of selection is as follows.
        Select a value between 1 and the minimum depth of the both offsprings,
        then select a random position on that level in the first offsp
        and a random position at the same distance from the last level as in the first one.
        :param off1: first offspring
        :param off2: second offspring
        :param prob: the probability of XO
        :return: the new offspring
        '''
        print("XO:", off1, off2)
        dimof1 = int(math.log2(len(off1.repres) + 1)) - 1
        dimof2 = int(math.log2(len(off2.repres) + 1)) - 1
        randLevel = random.randint(1, min(dimof1, dimof2))
        if dimof1 <= dimof2:
            startM = random.randint((2 ** randLevel) - 1, (2 ** (randLevel + 1)) - 2)
            startF = random.randint((2 ** (randLevel + max(dimof1, dimof2) - min(dimof1, dimof2))) - 1,
                                    (2 ** (randLevel + 1 + max(dimof1, dimof2) - min(dimof1, dimof2))) - 2)
        else:
            startF = random.randint((2 ** randLevel) - 1, (2 ** (randLevel + 1)) - 2)
            startM = random.randint((2 ** (randLevel + max(dimof1, dimof2) - min(dimof1, dimof2))) - 1,
                                    (2 ** (randLevel + 1 + max(dimof1, dimof2) - min(dimof1, dimof2))) - 2)

        if random.random() < prob:
            ##print("BEFORE CHANGING")
            ##off1.printInorder(0)
            ##print()
            ##off2.printInorder(0)
            ##print()
            self.swapSubTrees(off1, off2, startM, startF)
            #print("AFTER CHANGING")
            #off1.printInorder(0)
            #print()
            #off2.printInorder(0)
            #print()
        return []

    def swapSubTrees(self, off1, off2, start1, start2):
        if start1 >= len(off1.repres):
            return
        off1.repres[start1], off2.repres[start2] = off2.repres[start2], off1.repres[start1]
        self.swapSubTrees(off1, off2, (start1 << 1) + 1, (start2 << 1) + 1)
        self.swapSubTrees(off1, off2, (start1 << 1) + 2, (start2 << 1) + 2)

    def mutation(self, c, prob):
        # Cycle Mutation, Micro-Mutation
        if random.random() < prob:
            ##print("BEFORE MUTATION")
            ##c.printInorder(0)
            ##print()
            off = Chromosome()
            pos = randint(0, c.size - 1)
            off.repres = c.repres[:]
            off.size = c.size
            if off.repres[pos] > 0: #terminal
                off.repres[pos] = randint(1, noTerminals)
            else:   #function
                off.repres[pos] = -randint(1, noFunctions)
           #print("AFTER MUTATION")
           #c.printInorder(0)
           #print()
            return off
        return c

    def printInorder(self, pos):
        if pos >= len(self.repres):
            return
        self.printInorder((pos << 1) + 1)
        if self.repres[pos] < 0:
            print(functions[-self.repres[pos] - 1], " ", end='')
        else:
            print(terminals[self.repres[pos] - 1], " ", end='')
        self.printInorder((pos << 1) + 2)