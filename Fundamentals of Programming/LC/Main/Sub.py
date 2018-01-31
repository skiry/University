'''
Created on 3 dec. 2017

@author: Skiry
'''
from Main.StringToDigit import *
def subtraction(number1, number2, base):
    '''
    input : 2 numbers and the base in which the subtraction will be made
    output : a string with the corresponding result
    '''
    finalResult = []
    lenFinalResult = max(len(number1),len(number2)) 
    # the final result will have the lenght of the greater number
    for i in range(0,lenFinalResult):
        finalResult.append(0)
    for i in number1:
        if strToDigit(i) >= base:
            raise Exception("This is not base "+str(base))
    for i in number2:
        if strToDigit(i) >= base:
            raise Exception("This is not base "+str(base))
    i = len(number1) - 1
    j = len(number2) - 1
    lenFinalResult -= 1
    carry = 0
    while i != -1 and j != -1:
        # subtract the numbers until we finished the smaller number
        try:
            finalResult[lenFinalResult] = strToDigit(number1[i]) - strToDigit(number2[j]) - carry
            if finalResult[lenFinalResult] < 0:
                finalResult[lenFinalResult] += base
                carry = 1
            else:
                carry = 0
        except Exception:
            print("The numbers are incorrect!")
        i -= 1
        j -= 1
        lenFinalResult -= 1
        
    # if the second number is less than the first one, then we have to complete the 
    # remaining digits of the first one in the Result list
    while i != -1:
        finalResult[lenFinalResult] = strToDigit(number1[i]) - carry
        if finalResult[lenFinalResult] < 0:
            finalResult[lenFinalResult] += base
            carry = 1
        else:
            carry = 0
        i -= 1
        lenFinalResult -= 1
    return finalResult
