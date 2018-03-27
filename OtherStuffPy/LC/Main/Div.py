'''
Created on 3 dec. 2017

@author: Skiry
'''
from Main.StringToDigit import *
def division(number1, number2, base):
    '''
    input : 2 numbers and the base in which the division will be made
    output : a string with the corresponding result
    '''
    finalResult = []
    lenFinalResult = len(number1)
    # the final result will have the lenght of the first number or less
    lenFinalResult = 0
    # we check if the first digit is greater than the number to divide and if so, we put the quotient on the first position
    # in the result vector, otherwise we continue normally with the "carry" and a digit from the first number
    try:
        if strToDigit(number1[0]) >= strToDigit(number2):
            finalResult.append(0)
            finalResult[0] = strToDigit(number1[0]) // strToDigit(number2)
            lenFinalResult = 1
        carry = strToDigit(number1[0]) % strToDigit(number2)
    except Exception:
        print("The numbers are incorrect!")
    if len(number1) > 1:
        for i in range(1,len(number1)):
            try:  
                finalResult.append(0)
                finalResult[lenFinalResult] = carry * base + strToDigit(number1[i])
                carry = finalResult[lenFinalResult] % strToDigit(number2)
                finalResult[lenFinalResult] //= strToDigit(number2)
            except Exception:
                print("The numbers are incorrect!")
            lenFinalResult += 1
        
    return (finalResult,carry)
