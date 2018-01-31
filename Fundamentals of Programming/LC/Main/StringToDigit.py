'''
Created on 3 dec. 2017

@author: Skiry
'''
def strToDigit(number):
    '''
    input : a character
    output : the integer value of the character
    ex : 'F' = 15, '9' = 9
    '''
    try:
        number = int(number)
    except Exception:
        if number >= 'A' and number <= 'F':
            number = ord(number) - 55
        elif number >= 'a' and number <= 'f':
            number = ord(number) - 87
        number = int(number)
    return number
   