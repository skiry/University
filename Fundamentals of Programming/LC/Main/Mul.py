'''
Created on 3 dec. 2017

@author: Skiry
'''
from Main.StringToDigit import *
def multiplication(number1, number2, base):
    '''
    input : 2 numbers and the base in which the multiplication will be made
    output : a string with the corresponding result
    '''
    finalResult = []
    lenFinalResult = len(number1)
    # the final result will have the lenght of the first number + 1
    # because of the possible carry
    for i in range(0,lenFinalResult + 1):
        finalResult.append(0)
    i = len(number1) - 1
    carry = 0
    while i != -1:
        # multiply till we reach the first digit
        try:
            partialMultiplication = strToDigit(number1[i]) * strToDigit(number2) + carry
            finalResult[lenFinalResult] = partialMultiplication % base
            carry = partialMultiplication // base
        except Exception:
            print("The numbers are incorrect!")
        i -= 1
        lenFinalResult -= 1
    finalResult[lenFinalResult] = carry
    
    return finalResult
