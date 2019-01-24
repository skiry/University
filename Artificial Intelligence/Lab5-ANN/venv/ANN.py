'''
Establish if a patient suffers of disk hernia, spondilose or if is healthy
based on the informations collected from other patients (regarding the
shape and the orientation of the pelvis and the lumbar section of the spine).
The training data will be taken from:
  ​http://archive.ics.uci.edu/ml/datasets/Vertebral+Column
'''

from random import random
from math import exp, sin
from copy import deepcopy
import matplotlib as mpl
import matplotlib.pyplot
import numpy as np
import time

def identical(x):
    return x

def dIdentical(x):
    return 1

def ReLU(x):
    return max(0, x)

def dReLU(x):
    if x > 0:
        return 1
    else:
        return 0

def threshold(x):
    if x > 2.5:
        return 1
    return 0

def dThreshold(x):
    # is just to have some function when we train the network
    return 1

def sigmoid(x):
    return (1.0 / (1.0 + exp(-x)))


def dSigmoid(x):
    return x * (1.0 - x)

class Neuron:
    def __init__(self, noOfInputs, activationFunction):
        np.random.seed(int(time.time()))
        self.noOfInputs = noOfInputs
        self.activationFunction = activationFunction
        self.weights = [random() for x in range(self.noOfInputs)]
        self.output = 0

    def setWeights(self, weights):
        self.weights = weights

    def fireNeuron(self, inputs, outData):
        res = sum([x * y for x, y in zip(inputs, self.weights)])
        self.output = self.activationFunction(res)
        #print(res, "BEFORE ACTIV<--->AFTER ACTIV", self.output, "---EXPECTED -->", outData)
        return self.output

    def __str__(self):
        return "{weights}->" + str(self.weights) + '\n' + "{output}->" + str(self.output) + '\n'

class Layer:
    def __init__(self, noOfInputs, activationFunction, noOfNeurons):
        self.noOfNeurons = noOfNeurons
        self.neurons = [Neuron(noOfInputs, activationFunction) for x in range(self.noOfNeurons)]

    def forward(self, inputs, outData):
        for x in self.neurons:
            x.fireNeuron(inputs, outData)
        return ([x.output for x in self.neurons])

    def __str__(self):
        res = ""
        for i in range(len(self.neurons)):
            res += "Neuron " + str(i) + " has " + str(self.neurons[i])
        return res

class FirstLayer(Layer):
    def __init__(self, noOfNeurons, bias=False):
        if bias:
            noOfNeurons += 1
        Layer.__init__(self, 1, sigmoid, noOfNeurons)
        for x in self.neurons:
            x.setWeights([np.random.random()])

    def forward(self, inputs, outData):
        for x in range(len(self.neurons)):
            self.neurons[x].fireNeuron([inputs[x]], outData)
        return ([x.output for x in self.neurons])

class Network:
    def __init__(self, structure, activationFunction, derivate, bias=False):
        self.structure = structure
        self.activationFunction = activationFunction
        self.derivate = derivate
        self.bias = bias
        self.noLayers = len(self.structure)
        self.layers = [FirstLayer(self.structure[0], bias)]
        for i in range(1, self.noLayers):
            self.layers += [Layer(self.structure[i - 1], activationFunction, self.structure[i])]


    def feedForward(self, inputs, outData):
        self.synapses = inputs
        if self.bias:
            self.synapses.append(1)
        for x in self.layers:
            self.synapses = x.forward(self.synapses, outData)
        return self.synapses

    def computeLoss(self, inData, outData):
        loss = []
        actualResult = self.feedForward(inData, outData)
        for i in range(len(outData)):
            loss.append(outData[i] - actualResult[i])
        return loss

    def backPropagation(self, loss, learnRate):
        err = loss
        delta = []

        #start from the last layer
        currentLayer = self.noLayers - 1
        #create a copy for the network to be replaced after modifications
        newNetwork = Network(self.structure, self.activationFunction, self.derivate, self.bias)

        for i in range(self.structure[-1]):
            delta.append(err[i] * self.derivate(self.layers[-1].neurons[i].output))
            for j in range(self.structure[currentLayer - 1]):
                newNetwork.layers[-1].neurons[i].weights[j] = self.layers[-1].neurons[i].weights[j] + \
                    learnRate * delta[i] * self.layers[currentLayer - 1].neurons[j].output

        #iterate layer by layer going backwards to the first layer
        for currentLayer in range(self.noLayers - 2, 0, -1):
            currentDelta = []

            for i in range(self.structure[currentLayer]):
                currentDelta.append(self.derivate(self.layers[currentLayer].neurons[i].output) * \
                                    sum([self.layers[currentLayer + 1].neurons[j].weights[i] * delta[j] \
                        for j in range(self.structure[currentLayer + 1])]))

            delta = currentDelta
            for i in range(self.structure[currentLayer]):
                for j in range(self.structure[currentLayer - 1]):
                    newNetwork.layers[currentLayer].neurons[i].weights[j] = \
                    self.layers[currentLayer].neurons[i].weights[j] + learnRate *\
                        delta[i] * self.layers[currentLayer - 1].neurons[j].output

        self.layers = deepcopy(newNetwork.layers)

    def __str__(self):
        res = ""
        for i in range(len(self.layers)):
            res += "Layer " + str(i) + " : " + str(self.layers[i])
        return res





def test1():
    nn = Network([2, 2, 2, 2, 1], threshold, dThreshold)  # sigmoid, dSigmoid)#
    #u = [[0, 0, 1], [0, 1, 1], [1, 0, 1], [1, 1, 1]]
    #t = [[0], [1], [1], [20]]
    u = [[0, 1], [1, 0], [1, 1], [0, 0]]
    t = [[0], [0], [1], [0]]
    errors = []
    iterations = []
    for i in range(1500):
        iterations.append(i)
        e = []
        for j in range(len(u)):
            e.append(nn.computeLoss(u[j], t[j])[0])
            nn.backPropagation(nn.computeLoss(u[j], t[j]), 1)
        errors.append(sum([x ** 2 for x in e]))
    for j in range(len(u)):
        print(u[j], t[j], nn.feedForward(u[j]))
    print(str(nn))
    mpl.pyplot.plot(iterations, errors, label='loss value vs iteration')
    mpl.pyplot.xlabel('Iterations')
    mpl.pyplot.ylabel('loss function')
    mpl.pyplot.legend()
    mpl.pyplot.show()


def test2():
    #startOfParams
    layerss = [[6, 1],[6, 7, 9, 7, 1],[6, 6, 7, 9, 6, 1],[6, 6, 1],[6, 5, 1], [6, 8, 1], [6, 6, 6, 1]]
    noOfIterationss = [15,5,30]
    learningRates = [0.001,0.0000001, 0.0000355,3,1,0.8,0.3,0.1,0.05,0.002,0.00035]
    activFuncs = [ReLU, threshold, sigmoid]
    dActivFuncs = [dReLU, dThreshold, dSigmoid]
    #endOfParams

    filename = "column_2C.dat"
    results = {'AB': 0, 'NO': 1}
    inputDataAB = []
    expectedResultsAB = []
    inputDataNO = []
    expectedResultsNO = []
    with open(filename, "r") as openfileobject:
        for line in openfileobject:
            data = line.split()
            if results[data[6]] == 0:
                inputDataAB.append([float(data[0]), float(data[1]), float(data[2]), float(data[3]), \
                                  float(data[4]), float(data[5])])
                expectedResultsAB.append([results[data[6]]])
            else:
                inputDataNO.append([float(data[0]), float(data[1]), float(data[2]), float(data[3]), \
                                    float(data[4]), float(data[5])])
                expectedResultsNO.append([results[data[6]]])

    cnt = 0
    for layers in layerss:
        for learningRate in learningRates:
            for x in range(len(activFuncs)):
                for noOfIterations in noOfIterationss:
                    cnt += 1
                    activFunc = activFuncs[x]
                    dActivFunc = dActivFuncs[x]
                    wrt = open(str(cnt) + ".txt", "w")
                    wrt.write(str(layers) + "\n")
                    wrt.write(str(noOfIterations) + " no of iterations\n")

                    wrt.write(str(learningRate) + " learning rate \n")
                    wrt.write(str(activFunc) + "\n")
                    nn = Network(layers, activFunc, dActivFunc)
                    #210 && 100
                    u = inputDataAB[:170]
                    u += inputDataNO[:70]
                    t = expectedResultsAB[:170]
                    t += expectedResultsNO[:70]

                    errors = []
                    iterations = []
                    for i in range(noOfIterations):
                        iterations.append(i)
                        e = []
                        for j in range(len(u)):
                            e.append(nn.computeLoss(u[j], t[j])[0])
                            nn.backPropagation(nn.computeLoss(u[j], t[j]), learningRate)
                        errors.append(sum([x ** 2 for x in e]))
                    FP = 0
                    FN = 0
                    TP = 0
                    TN = 0
                    for j in range(len(u)):
                        res = nn.feedForward(u[j], t[j])
                        #print(u[j], t[j], res)
                        if res[0] > 0.44:
                            res[0] = 1
                        else:
                            res[0] = 0
                        if t[j] == res:
                            if res[0] == 0:
                                TP += 1
                            elif res[0] == 1:
                                TN += 1
                        else:
                            if res[0] == 0:
                                FP += 1
                            elif res[0] == 1:
                                FN += 1
                    #print(str(nn))
                    #print(str(TP + TN) + " correct out of 240 on input data")
                    #print(str((TP + TN) / 2.4) + "% on input data")
                    #print("Sick and sick: " + str(TP))
                    #print("Healthy and healty: " + str(TN))
                    #print("Sick and healthy: " + str(FN))
                    #print("Healthy and sick: " + str(FP))

                    wrt.write(str(nn) + "\n")
                    wrt.write(str(TP + TN) + " correct out of 240 on input data" + "\n")
                    wrt.write(str((TP + TN) / 2.4) + "% on input data" + "\n")
                    wrt.write("Sick and sick: " + str(TP) + "\n")
                    wrt.write("Healthy and healthy: " + str(TN) + "\n")
                    wrt.write("Sick and healthy: " + str(FN) + "\n")
                    wrt.write("Healthy and sick: " + str(FP) + "\n" + "\n")

                    if (TP + TN) / 2.4 > 60 and ((TP ==0 and TN*FN*FP != 0) or \
                            (TN ==0 and TP*FN*FP != 0) or (FP ==0 and TN*FN*TP != 0) or\
                            (FN ==0 and TN*TP*FP != 0) or (TP*TN*FP*FN != 0)):
                        gd = open(str(cnt) + "isOk.txt", "w")
                        gd.write(str(layers) + "\n")

                    u = inputDataAB[170:]
                    u += inputDataNO[70:]
                    t = expectedResultsAB[170:]
                    t += expectedResultsNO[70:]
                    FP = 0
                    FN = 0
                    TP = 0
                    TN = 0
                    for j in range(len(u)):
                        res = nn.feedForward(u[j], t[j])
                        #print(u[j], t[j], res)
                        if res[0] > 0.44:
                            res[0] = 1
                        else:
                            res[0] = 0
                        if t[j] == res:
                            if res[0] == 0:
                                TP += 1
                            elif res[0] == 1:
                                TN += 1
                        else:
                            if res[0] == 0:
                                FP += 1
                            elif res[0] == 1:
                                FN += 1

                    #print(str(TP + TN)  + " correct out of 70 on test data")
                    #print(str((TP + TN) / 0.7) + "% on test data")
                    #print("Sick and sick: " + str(TP))
                    #print("Healthy and healty: " + str(TN))
                    #print("Sick and healthy: " + str(FN))
                    #print("Healthy and sick: " + str(FP))
#
                    #wrt.write(str(nn))
                    wrt.write(str(TP + TN) + " correct out of 70 on test data" + "\n")
                    wrt.write(str((TP + TN) / 0.7) + "% on test data" + "\n")
                    wrt.write("Sick and sick: " + str(TP) + "\n")
                    wrt.write("Healthy and healty: " + str(TN) + "\n")
                    wrt.write("Sick and healthy: " + str(FN) + "\n")
                    wrt.write("Healthy and sick: " + str(FP) + "\n")
                    if (TP + TN) / 2.4 > 60 and ((TP ==0 and TN*FN*FP != 0) or \
                            (TN ==0 and TP*FN*FP != 0) or (FP ==0 and TN*FN*TP != 0) or\
                            (FN ==0 and TN*TP*FP != 0) or (TP*TN*FP*FN != 0)):
                        gd = open(str(cnt) + "isOkAgain.txt", "w")
                        gd.write(str(layers) + "\n")
                    #mpl.pyplot.plot(iterations, errors, label='loss value vs iteration')
                    #mpl.pyplot.xlabel('Iterations')
                    #mpl.pyplot.ylabel('loss function')
                    #mpl.pyplot.legend()
                    #mpl.pyplot.show()


# test1()
test2()




















