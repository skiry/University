menu = """
       1. Addition in base p
       2. Subtraction in base p
       3. Multiplication in base p by one digit
       4. Division in base p by one digit
       5. Conversion between 2 bases
       6. Exit
       """
from Main.StringToDigit import *
from Main.Add import *
from Main.Sub import *
from Main.Mul import *
from Main.Div import *
def digitToStr(number):
    '''
    input : an integer
    output : the corresponding character for the int value
    ex : 15 = 'F', 9 = '9'
    '''
    if number >= 10 and number <= 15:
        number += 55
        number = chr(number)
    return number     

def powOf2(number):
    '''
    input : an integer
    output : True, if number is a power of 2
             False, otherwise
    ex : 16 -> True, 9 -> False
    '''
    if number == 2 or number == 4 or number == 8 or number == 16:
        return True
    return False 

def rapidConversion(fromBase, toBase, number):
    '''
    input : 2 bases (powers of 2) and a number to convert
    output : a string with the corresponding result
    '''
    # value  = how much bits we need to fill in when converting to base 2
    if fromBase == 4:
        value = 2
    elif fromBase == 8:
        value = 3
    else:
        value = 4
        
    
    # if the fromBase is different from 2, we convert it to 2 
    if fromBase != 2:
        finalResult = []
        lenFinalResult = value * len(number)
        for i in range(0,lenFinalResult):
            finalResult.append(0)
        lenFinalResult = 0
        for i in number:
            digit = strToDigit(i)
            lenFinalResult += value - 1 # we have to fill in from right to left: ex: 6%2=0 3%2=1 1%2=1 -> result 110, not 011
            for j in range(0,value):
                finalResult[lenFinalResult] = digit % 2
                digit //= 2
                lenFinalResult -= 1
            lenFinalResult += value + 1# then pass the "value" bits ( 3 in case of base 8 ) + 1 because of the last subtraction
    else:
        finalResult = []
        lenFinalResult = len(number)
        for i in number:
            finalResult.append(strToDigit(i))        
    # if toBase is 2, we finished, otherwise, convert to toBase
    # value  = how much bits we need to fill in when converting from base 2
    if toBase == 4:
        value = 2
    elif toBase == 8:
        value = 3
    else:
        value = 4
    result = []
    lenResult = lenFinalResult // value + 1
    # the lenght of the final list is the actual lenght divided by 
    # the number of bits we will go through in each iteration
    for i in range(0,lenResult):
        result.append(0)
    lenResult -= 1
    if toBase != 2:
        i = lenFinalResult - 1
        while i >= 0:
            for j in range(0,value):
                if i >= 0: # we check to make sure we do not acces elements that are not in out array
                    result[lenResult] += finalResult[i] * ( 2 ** j)
                # ex of the above function: for base 8, j will be 0,1,2 in each iteration
                # so, we need to put the result in the following way: 0/1 * 1 + 0/1 * 2 + 0/1 * 4
                # which is exactly the bit multiplied by 2 at the power of j
                i -= 1
            lenResult -= 1
    else:
        return finalResult   
    return result
            
def succesiveDivisions(fromBase, toBase, number):
    '''
    input : 2 bases ( fromBase > toBase ) and a number to convert
    output : a string with the corresponding result
    '''
    finalResult = []
    lenFinalResult = 0
      
    while True:
        partialResult = division(number, toBase, fromBase) 
        # succesively divide the quotient to the base in which we want the conversion
        finalResult.append(0)
        finalResult[lenFinalResult] = partialResult[1]
        number = ""
        # because partialResult[0] is an array, we need to make it a string
        # this is our convention because this is how division() function works
        for i in partialResult[0]:
            number += str(digitToStr(i))
        if len(number) == 0:
            break
        lenFinalResult += 1
    finalResult.reverse()
    return finalResult
    
def substitution(fromBase, toBase, number):
    '''
    input : 2 bases ( fromBase < toBase ) and a number to convert
    output : a string with the corresponding result
    '''
    finalResult = []
    lenFinalResult = 0
    
    number = list(number)
    number.reverse()
    
    result = 0
    try:
        for i in range(0,len(number)):
            intermediar = "1"
            for j in range(0,i):
                partial = multiplication(intermediar, str(fromBase), toBase)
                intermediar = ""
                for k in partial:
                    intermediar += digitToStr(k)
            partial = multiplication(intermediar, number[i], toBase)
            intermediar = ""
            for k in partial:
                intermediar += digitToStr(k)
            resultString = ""
            for j in result:
                resultString += digitToStr(j)
            result = addition(intermediar,resultString,toBase)
    except Exception:
        print("Incorrect numbers!")
    return result

def substitution10(fromBase, toBase, number):
    '''
    input : 2 bases and a number to convert by intermediate base 10
    output : a string with the corresponding result
    '''
    finalResult = []
    lenFinalResult = 0
    
    number = list(number)
    number.reverse()
    
    result = 0
    try:
        for i in range(0,len(number)):
            result += (fromBase ** i) * strToDigit(number[i])
        final = succesiveDivisions(10, str(toBase), str(result))
    except Exception:
        print("Incorrect numbers!")
    return final  

def UI():
    '''
    the main program
    '''
    print("Hi. Welcome to my program!")
    while True:
        print(menu)
        choose = input()
        try:
            choose = int(choose)
            if choose not in range(1,7):
                raise Exception
        except Exception:
            print("Choose a valid option!")
        if choose == 6:
            break
        elif choose == 1:
            base = input("Base: ")
            try:
                base = int(base)
                if base not in range(1,17):
                    raise Exception("Invalid base!")
                number1 = input("First number: ")
                number2 = input("Second number: ")
                result = addition(number1, number2, base)
                j = 0
                while result[j] == 0:
                    j += 1
                for i in range(j,len(result)):
                    print(digitToStr(result[i]), end="")
            except Exception as exc:
                print(exc)
        elif choose == 2:
            base = input("Base: ")
            try:
                base = int(base)
                if base not in range(1,17):
                    raise Exception("Invalid base!")
                number1 = input("The greater number: ")
                number2 = input("The second one: ")
                # we check if the first number is greater than the second one, if not, throw an exception
                if len(number1) < len(number2):
                    raise Exception("Please respect the rules.")
                elif len(number1) == len(number2):
                    ok = 1
                    for i,j in zip(number1,number2):
                        if i < j and ok:
                            raise Exception("Please respect the rules.") 
                        elif i > j:
                            ok = 0
                result = subtraction(number1, number2, base)
                j = 0
                while result[j] == 0:
                    j += 1
                for i in range(j,len(result)):
                    print(digitToStr(result[i]), end="")
            except Exception as exc:
                print(exc)
        elif choose == 3:
            base = input("Base: ")
            try:
                base = int(base)
                if base not in range(1,17):
                    raise Exception("Invalid base!")
                number1 = input("Number: ")
                number2 = input("Digit: ")
                if len(number2) > 1:
                    raise Exception("One digit for the 2nd number")
                result = multiplication(number1, number2, base)
                j = 0
                while result[j] == 0:
                    j += 1
                for i in range(j,len(result)):
                    print(digitToStr(result[i]), end="")
            except Exception as exc:
                print(exc)
        elif choose == 4:
            base = input("Base: ")
            try:
                base = int(base)
                if base not in range(1,17):
                    raise Exception("Invalid base!")
                number1 = input("Number: ")
                number2 = input("Digit: ")
                if len(number2) > 1:
                    raise Exception("One digit for the 2nd number")
                result = division(number1, number2, base)
                j = 0
                while result[j] == 0:
                    j += 1
                print("Quotient: ", end="")
                for i in result[0]:
                    print(digitToStr(i), end="")
                print("\nRemainder: ",digitToStr(result[1]))
            except Exception as exc:
                print(exc)
        elif choose == 5:
            fromBase = input("Convert from base: ")
            toBase = input("To base: ")
            try:
                fromBase = int(fromBase)
                toBase = int(toBase)
                if fromBase not in range(1,17) or toBase not in range(1,17):
                    raise Exception("Invalid base!")
                number = input("Number: ")
                if powOf2(fromBase) and powOf2(toBase):
                    print("We used rapid conversions!")
                    result = rapidConversion(fromBase,toBase,number)
                elif fromBase > toBase:
                    print("We used succesive divisions!")
                    result = succesiveDivisions(fromBase, str(toBase), number)
                else:
                    print("We used substitution!")
                    result = substitution10(fromBase, toBase, number)
                j = 0
                while result[j] == 0:
                    j += 1
                for i in range(j,len(result)):
                    print(digitToStr(result[i]), end="")
            except Exception as exc:
                print(exc)
UI()