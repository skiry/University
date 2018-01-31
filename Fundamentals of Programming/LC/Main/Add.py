'''
Created on 3 dec. 2017

@author: Skiry
'''
from Main.StringToDigit import *
def addition(number1, number2, base):
    '''
    input : 2 numbers to be added and the base in which the addition will be made
    output : a string with the corresponding result
    '''
    finalResult = []
    lenFinalResult = max(len(number1),len(number2)) 
    # the final result will have the lenght of the greater number + 1
    # because of the possible carry
    for i in range(0,lenFinalResult + 1):
        finalResult.append(0)
    for i in number1:
        if strToDigit(i) >= base:
            raise Exception("This is not base "+str(base))
    for i in number2:
        if strToDigit(i) >= base:
            raise Exception("This is not base "+str(base))
    i = len(number1) - 1
    j = len(number2) - 1
    carry = 0
    while i != -1 and j != -1:
        # add the numbers until we finished the smaller number
        try:
            finalResult[lenFinalResult] += carry + strToDigit(number1[i]) + strToDigit(number2[j])
            carry = finalResult[lenFinalResult] // base
            finalResult[lenFinalResult] %= base
        except Exception:
            print("The numbers are incorrect!")
        i -= 1
        j -= 1
        lenFinalResult -= 1
    
    # the following two whiles are in case of one finished string and the other still having digits
    while i != -1:
        finalResult[lenFinalResult] += carry + strToDigit(number1[i])
        carry = finalResult[lenFinalResult] // base
        finalResult[lenFinalResult] %= base
        i -= 1
        lenFinalResult -= 1
    while j != -1:
        finalResult[lenFinalResult] += carry + strToDigit(number2[j])
        carry = finalResult[lenFinalResult] // base
        finalResult[lenFinalResult] %= base
        j -= 1
        lenFinalResult -= 1
    finalResult[lenFinalResult] = carry
    return finalResult
