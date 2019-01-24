'''
Build a system that approximate the quality of a concrete mixture
based on the used ingredients.
The training data will be taken from:
http://archive.ics.uci.edu/ml/datasets/Concrete+Slump+Test
'''
from Algorithm import Algorithm
import sys
sys.setrecursionlimit(10000)

if __name__ == '__main__':
    alg = Algorithm("slump_test.data")

    pop, prob = alg.run()
    alg.population.evaluate(pop, prob)