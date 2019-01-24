from random import *

class Ant:
    def __init__(self, n, m, words, positions, lengths, directions):
        '''
        Initialize a solution by randomly picking a word and a valid position
        :param n: width of the crossword matrix
        :param m: height of the crossword matrix
        :param words: number of words to be fitted in the matrix
        :param positions: the number of starting position for the words
        :param lengths: the lengths of the starting positions
        :param directions: the directions of the starting positions
                'r' : the word goes to the right
                'd' : the word goes down
        '''
        self.n = n
        self.m = m
        self.words = words
        self.positions = positions
        self.lengths = lengths
        self.directions = directions

        self.solution = []
        for i in range(self.m):
            line = []
            for j in range(self.n):
                line.append("-")
            self.solution.append(line)

        self.viz = [0 for x in range(len(self.words))]
        self.posViz = [0 for x in range(len(self.words))]

        wordCounter = randint(0, len(words) - 1)
        word = self.words[wordCounter]
        self.viz[wordCounter] = 1

        possibleChoice = []
        for i in range(len(words)):
            if self.lengths[i] == len(word):
                possibleChoice.append(i)

        chosen = randint(0, len(possibleChoice) - 1)
        self.posViz[possibleChoice[chosen]] = 1
        startPosX = self.positions[possibleChoice[chosen]][0]
        startPosY = self.positions[possibleChoice[chosen]][1]
        if self.directions[possibleChoice[chosen]] == 'd':
            endPosX = startPosX + len(word)
            endPosY = startPosY + 1
        elif self.directions[possibleChoice[chosen]] == 'r':
            endPosX = startPosX + 1
            endPosY = startPosY + len(word)

        counter = 0
        for i in range(startPosX, endPosX):
            for j in range(startPosY, endPosY):
                self.solution[i][j] = word[counter]
                counter = counter + 1

        self.path = []
        self.path.append((wordCounter, self.positions[possibleChoice[chosen]]))

    def printSolution(self):
        for i in range(self.m):
            for j in range(self.n):
                print(self.solution[i][j], end='')
            print()
        print()

    def nextMoves(self):
        '''
        Compute the whole next moves of a random word, selectin the
        possible positions for it
        :return: the array containing the positions
        '''
        val = randint(0, len(self.words) - 1)
        while self.viz[val] == 1:
            val = randint(0, len(self.words) - 1)

        word = self.words[val]

        possibleChoice = []
        for i in range(len(self.words)):
            if self.lengths[i] == len(word) and self.posViz[i] == 0:
                possibleChoice.append(i)

        return possibleChoice.copy(), val

    def moveGoodness(self, word, position):
        '''
        Compute how good is the given word fitting in the next position
        :param word: the word being verified
        :param position: the position in which we want to put the word
        :return: a value denoting how good is this move
        '''
        startPosX = self.positions[position][0]
        startPosY = self.positions[position][1]
        if self.directions[position] == 'd':
            endPosX = startPosX + len(word)
            endPosY = startPosY + 1
        elif self.directions[position] == 'r':
            endPosX = startPosX + 1
            endPosY = startPosY + len(word)

        score = 0
        counter = 0
        for i in range(startPosX, endPosX):
            for j in range(startPosY, endPosY):
                if self.solution[i][j] != "-":
                    if self.solution[i][j] != word[counter]:
                        score = score - 1000
                    else:
                        score = score + 500
                else:
                    score = score + 250
                counter = counter + 1

        return score

    def fitness(self):
        '''
        The longer the path, the better - the sooner the solution will appear
        :return: the fitness value
        '''
        return len(self.words) - len(self.solution)

    def addMove(self, q0, trace, alpha, beta):
        '''
        Add a new position in the solution of the ant if it is possible
        :param q0: the probability of getting the best or a random one
        :param trace: the trace matrix
        :param alpha: alpha parameter
        :param beta: beta parameter
        :return: True if ant cand make a move, False otherwise
        '''
        possibleChoice, chosenWord = self.nextMoves()
        word = self.words[chosenWord]

        positions = [0 for i in range(len(self.words))]
        #mark with 0 unavailable positions
        if possibleChoice == []:
            return False
        else:
            for pos in possibleChoice:
                positions[pos] = self.moveGoodness(word, pos)
                #set an empiric value to a possible space
                positions[pos] = max(positions[pos], 1)
            positions = [(positions[i] ** beta) * (trace[(chosenWord, self.positions[i])] ** alpha) for i in range(len(positions))]

            if random() < q0:
                #add the best of the possible moves
                positions = [(i, positions[i]) for i in range(len(positions))]
                positions = max(positions, key=lambda a: a[1])
                self.path.append((chosenWord, self.positions[positions[0]]))
                startingPoint = positions[0]
            else:
                #add a move with some probability -i.e, roulette
                s = sum(positions)
                if s == 0:
                    return choice(possibleChoice)
                positions = [ positions[i] / s for i in range(len(positions))]
                positions = [ sum(positions[0:i + 1]) for i in range(len(positions))]

                r = random()
                i = 0

                while r > positions[i]:
                    i = i + 1
                self.path.append((chosenWord, self.positions[i]))
                startingPoint = i

            self.viz[chosenWord] = 1
            self.posViz[startingPoint] = 1

            startPosX = self.positions[startingPoint][0]
            startPosY = self.positions[startingPoint][1]

            if self.directions[startingPoint] == 'd':
                endPosX = startPosX + len(word)
                endPosY = startPosY + 1
            elif self.directions[startingPoint] == 'r':
                endPosX = startPosX + 1
                endPosY = startPosY + len(word)

            counter = 0
            putThis = True
            for i in range(startPosX, endPosX):
                for j in range(startPosY, endPosY):
                    if self.solution[i][j] != "-" and self.solution[i][j] != word[counter]:
                        putThis = False
                    counter = counter + 1

            if putThis:
                counter = 0
                for i in range(startPosX, endPosX):
                    for j in range(startPosY, endPosY):
                        self.solution[i][j] = word[counter]
                        counter = counter + 1

            return True