from Algorithm import Algorithm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

from functools import reduce
from random import randint, random
from statistics import pstdev
#Consider cubes of known sides’ length and colors . Assemble thehighest n
# si and colors ci pyramid from the cubes in such a way that it has ‘stability’
# (there is not a bigger cube over a smaller one) and there are not two consecutive cubes of the same color.
def main():
    print("Welcome to Pyramid Evoluationary Algorithm!")
    alg = Algorithm("data02.in")


    print(" 1 - Run.")
    print(" 2 - Run the benchmark.")
    print(" 3 - Run once and plot.")

    option = input("Choose an option: ").strip()

    if option == '1':
        pop, prob = alg.run()
        alg.population.evaluate(pop, prob)
    elif option == '2':
        runBenchmark()
    elif option == '3':
        runPlot()

def runPlot():

    alg = Algorithm("data02.in")
    alg.run()

    plt.hist(alg.getAllFitness(), 25, facecolor='blue', alpha=0.5)
    plt.show()

def runBenchmark():
    fitnesses = []
    bestFitness = None
    for i in range(1000):
        alg = Algorithm("data02.in")
        pop, prob = alg.run()
        bestFitness = alg.problem.numberOfGenes
        fitnesses.append(alg.population.getBest(pop, prob)[0])

    print(fitnesses)
    print('-' * 80)
    print("Fitness statistics.")
    print("Best possible fitness: " + str(bestFitness))
    print("The average of the best individuals: " + str(reduce(lambda x, y: x + y, fitnesses) / len(fitnesses)))
    print("The standard deviation of the best individuals: " + str(pstdev(fitnesses)))
    print('-' * 80)
main()