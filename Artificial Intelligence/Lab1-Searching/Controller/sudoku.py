'''Consider a Sudoku game - a logic puzzle represented on a ​ n x ​ n board; some squares contain already a number,
others must be completed  with other numbers from {​ 1,2,…,n } in such a way that each line, column and square with the
edge equal with √n must contain only different numbers. Determine one correct solution for the puzzle.
'''


class Controller:
    def __init__(self, problem):
        self.__instance = problem

    def BFS(self, root):
        q = [root]
        while len(q) > 0:
            currentState = q.pop(0)

            if self.__instance.checkFinalState(currentState):
                return currentState
            q = q + self.__instance.expand(currentState)

    def GBFS(self, root):
        q = [root]

        while len(q) > 0:
            currentState = q.pop(0)

            if self.__instance.checkFinalState(currentState):
                return currentState

            aux = [] + self.__instance.expand(currentState)

            self.orderStates(aux)

            q = aux[:] + q

    def orderStates(self, states):
        states = [[x, self.__instance.heuristic(x)] for x in states]
        states.sort(key=lambda x: x[1], reverse=True)
        states = [x[0] for x in states]
        return states

    def hasSolution(self):
        return self.__instance.hasSolution()