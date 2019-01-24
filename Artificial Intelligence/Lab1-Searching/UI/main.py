from Controller.sudoku import Controller
from Problem.problem import Problem
import time

class UI:
    def __init__(self, fileName):
        self.__p = Problem(fileName)
        self.__ctrl = Controller(self.__p)

    def main(self):
        print("Hi!")
        while 1:
            self.printInfo()
            #try:
            x = int(input())

            if x == 0:
                break
            elif x == 1:
                startClock = time.perf_counter()
                self.__ctrl.BFS(self.__p.getInitialState())

                if self.__ctrl.hasSolution() == False:
                    print("No solution")
                else:
                    print(self.__p)

                print('execution time = ', time.perf_counter() - startClock, " seconds")
            elif x == 2:
                startClock = time.perf_counter()
                self.__ctrl.GBFS(self.__p.getInitialState())

                if self.__ctrl.hasSolution() == False:
                    print("No solution")
                else:
                    print(self.__p)

                print('execution time = ', time.perf_counter() - startClock, " seconds")
            else:
                print("Incorrect choice!")
            #except:
                print("Invalid choice!")

    def printInfo(self):
        print("0. Exit")
        print("1. BFS")
        print("2. GBFS")


def main():
    ui = UI("largeinput2.txt")
    ui.main()

main()