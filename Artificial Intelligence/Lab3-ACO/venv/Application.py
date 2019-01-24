from Controller import Controller
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

from functools import reduce
from random import randint, random
from statistics import pstdev

def main():
    c = Controller()

    print(" 1 - Run.")
    print(" 2 - Run the benchmark.")
    print(" 3 - Run once and plot.")

    option = input("Choose an option: ").strip()

    if option == '1':
        print("LOADING...")
        sol, ant = c.run()
        print("The best solution found by the ants is: ", sol)
        c.printAntPath(ant)
    elif option == '2':
        runBenchmark()
    elif option == '3':
        runPlot()


def runPlot():
    c = Controller()
    c.run()

    plt.hist(c.getAllFitness(), 25, facecolor='blue', alpha=0.5)
    plt.show()


def runBenchmark():
    fitnesses = []
    bestFitness = None
    for i in range(1000):
        c = Controller()
        pop, ant = c.run()
        bestFitness = c.p.numberOfWords
        fitnesses.append(ant.fitness())

    print(fitnesses)
    print('-' * 80)
    print("Fitness statistics.")
    print("Best possible fitness: " + str(bestFitness))
    print("The average of the best individuals: " + str(reduce(lambda x, y: x + y, fitnesses) / len(fitnesses)))
    print("The standard deviation of the best individuals: " + str(pstdev(fitnesses)))
    print('-' * 80)

main()