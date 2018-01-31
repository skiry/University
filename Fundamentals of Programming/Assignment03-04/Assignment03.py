'''
John wants to manage his bank account. In order to complete this task, John needs an application to
store, for a given month, all the bank transactions performed on his account. Each transaction is
stored in the application using the following elements:
*day (of the month in which the transaction was made, between 0 and 30)
*amount of money (that was transferred, positive integer)
*type (in - into the account, out – from the account)
*description
'''
#### feature 4,5,6
#### update documentation
#### all assert test functions
#### 3 modules
#### get() functions
#### let user choose->question: UI or command based

###list of lists list[0]
def helpMe():
    menu='''       HELP PAGE
        add <value> <type> <description>
        insert <day> <value> <type> <description>

        remove <day>
        remove <start day> to <end day>
        remove <type>
        replace <day> <type> <description> with <value>

        list
        list <type>
        list [ < | = | > ] <value>
        list balance <day>
        '''
    print(menu)
    
def add(listt,params):
    '''
    add the tuple params to the list
    '''
    listt.append(params)
    
def testInit(listTr):
    '''
    a simple list with transactions for testing
    '''
    addThis=(1,10,"out","pizza")
    add(listTr,addThis)
    addThis=(2,100,"out","party")
    add(listTr,addThis)
    addThis=(3,20,"out","sauce")
    add(listTr,addThis)
    addThis=(5,35,"out","drink")
    add(listTr,addThis)
    addThis=(6,900,"in","salary")
    add(listTr,addThis)
    addThis=(7,50,"in","business")
    add(listTr,addThis)
    addThis=(8,10,"out","juice")
    add(listTr,addThis)
    addThis=(20,100,"in","lottery")
    add(listTr,addThis)
    addThis=(22,300,"in","gift")
    add(listTr,addThis)
    addThis=(30,550,"out","poker")
    add(listTr,addThis)
    
def printList(listTr):
    '''
    prints the entire list of transactions line by line
    '''
    for trans in listTr:
        print (trans)

def getCommand():
    '''
    Read and parse user's command
    '''
    cmd=input("Command: ")
    if cmd.find(" ")==-1:
        '''
        the user may have written help or exit or list
        '''
        command=cmd
        parameters=""
    else:
        command=cmd[:cmd.find(" ")]
        params=cmd[cmd.find(" ")+1:]
        if command=='add' or command=='remove':
            params=params.split(",")
            parameters=multipleAdd(params)
            for i in parameters:
                actual=i
                actual=actual.split(" ")
                for el in actual:
                    el=el.strip()
        else:
            params=params.split(" ")
            for i in range(len(params)):
                params[i]=params[i].strip()
            return (command,params)
        
    return (command,parameters)

def checkParam(param):
    '''
    checks if the sent parameter is either IN or OUT
    '''
    if param=='in' or param=='out':
        return True
    return False

def printListInOut(listTr,param):
    '''
    lists all the IN or OUT transactions
    ex : list in – write all the in transactions.
    '''
    param=param[0]
    if checkParam(param):
        for element in listTr:
            if element[2]==param:
                print (element)
    else:
        print("Error: You must require IN or OUT transactions!")

def checkSymbol(param):
    '''
    checks if the symbol is < or = or >
    '''
    if param=='<':
        return 1
    elif param=='=':
        return 2
    elif param=='>':
        return 3
    return False

def checkInteger(param):
    '''
    checks if a parameter is an integer
    '''
    param=str(param)
    return param.isdigit()

def validDay(day):
    '''
    checks if the DAY parameter is in the interval [1,31]
    '''
    if day>=1 and day<=31:
        return True
    return False

def balance(listTr,param):
    '''
    prints the account balance on the day PARAM.
        ex : list balance 10 – computes the account’s balance on day 10. This is the sum of all in
    transactions, from which we subtract out transactions occurring before or on day 10.
    '''
    if checkInteger(param) and validDay(int(param)):
        sumIs=0
        for day in listTr:
            if day[0]<=int(param):
                if day[2]=='in':
                    sumIs+=day[1]
                else:
                    sumIs-=day[1]
        return sumIs
    return False

def printBalance(listTr,param):
    '''
    calls the balance() function above and checks if the parameter is a positive number within [1,31] and prints friendly texts
    '''
    result=balance(listTr,param)
    if result:
        print("Your balance on day ",param," is ", result)
    else:
        print("Error: You want your balance on a day of a month [1,31] or what...?")
        
def printListSEG(listTr,params):
    '''
    print List; Smaller/Greater than a value; Equal with a value
    '''
    symbol=checkSymbol(params[0])
    if checkInteger(params[1]):
        value=int(params[1])
        if symbol==1:
            for element in listTr:
                if element[1]<value:
                    print (element)
        elif symbol==2:
            for element in listTr:
                if element[1]==value:
                    print (element)
        elif symbol==3:
            for element in listTr:
                if element[1]>value:
                    print (element)
        else:
            print("Error: PAY ATTENTION : list [ < | = | > ] <value>")
    else:
        print("Error: Don't be a troll, enter an integer!")

def removeDay(listTr,day):
    '''
    removes all transactions from day DAY
    ex : remove 15 – remove all transactions from day 15
    '''
    removedIs=0
    for element in reversed(listTr):
        if element[0]==day:
            listTr.remove(element)
            removedIs=1
    if removedIs:
        return True
    return False

def removeSymbol(listTr,symb):
    '''
    removes all IN / OUT transactions
    ex : remove in – remove all the in transactions from the current month
    '''
    
    removedIs=0
    for element in reversed(listTr):
        if element[2]==str(symb):
            listTr.remove(element)
            removedIs=1
    if removedIs:
        return True
    return False

def removeList(listTr,params):
    '''
    checks what to remove: day, in transactions or out transactions
    prints nice texts
    '''
    for i in params:
        actual=i
        actual=actual.split(" ")
        for el in actual:
            el=el.strip()
        param=actual[0]
        if checkInteger(param):
            if validDay(int(param)):
                if removeDay(listTr,int(param)):
                    print("All transactions from day ",param," removed!")
                else:
                    print("There are no transactions on day ",param)
            else:
                print("When you will be in the day ",param," of the month, call me!")
        elif param=='in' or param=='out':
            if removeSymbol(listTr,param):
                print("All the ",param," transactions from the entire month have been removed!")
            else:
                print("There are no ",param," transactions!")
        else: print("Error: What do you want to remove? Pay attention!")
        
def replace(listTr,params):
    '''
    replace 12 in salary with 2000 – replace the amount for the in transaction having the “salary”
description from day 12 with 2000 RON

    '''
    
    from copy import deepcopy
    okList=[]
    change=0
    if validReplace(listTr,params):
        for el in listTr:
            if el[0]==int(params[0]) and el[2]==params[1] and el[3]==params[2]: 
                mytuple=(el[0],int(params[4]),el[2],el[3])
                el=deepcopy(mytuple)
                change=1
            add(okList,el)
        if change:
            print("Ok!")
        else:
            print("Error: This is not what you were trying to write, isn't it?")
    return okList

def validReplace(listTr,params):
    '''
    checks all the parameters for the replace() function in order to work correctly
    '''
    day=params[0]
    typeOf=params[1]
    descr=params[2]
    suma=params[4]
    if checkInteger(day):
        if validDay(int(day)):
            if typeOf=='in' or typeOf=='out':
                if descr.isalpha():
                    if params[3]=='with':
                        if checkInteger(suma):                                                              #iuliana@cs.ubbcluj.ro-LAB3-scs
                            return True
                        else:
                            print("Error: You must replace this transaction with an integer value!")
                    else:
                        print("....WITH...write WITH!!!")
                else:
                    print("Error: Please write a valid description!")
            else:
                print("Error: No other types of transactions are available, just IN and OUT!")
        else:
            print("Error: You must replace something in the interval [1,31]!")
    else:
        print("Error: The first parameter must be an integer!")
    return False

def removeFromTo(listTr,fromDay,toDay):
    '''
    removes all transactions between two given days
    remove 5 to 10 – removes all transactions between day 5 and day 10.

    '''
    if checkInteger(fromDay) and validDay(int(fromDay)) and validDay(int(toDay)) and checkInteger(toDay):
        for elements in reversed(listTr):
            if elements[0]>=int(fromDay) and elements[0]<=int(toDay):
                listTr.remove(elements)
        print("Everything was deleted from day ",fromDay," to day ",toDay)
    else:
        print("Error: Seriously...?")

def currentDay():
    '''
    this functions returns the current day of the month"
    '''
    import time
    day=time.strftime("%d")
    return day

def start():
    '''
    the start of the program
    '''
    listTr=[]
    testInit(listTr)
    while True:
        cmd=getCommand()
        action=cmd[0]
        params=cmd[1]
        if action=='exit':
            break
        elif action=='help':
            helpMe()
        elif action=='list' and len(params)==0:
            printList(listTr)
        elif action=='list' and len(params)==1:
            printListInOut(listTr,params)
        elif action=='list' and len(params)==2 and str(params[0])!=str('balance'):
            printListSEG(listTr,params)
        elif action=='list' and len(params)==2:
            printBalance(listTr,params)
        elif action=='remove':
            ok=0
            for i in params:
                actual=i
                actual=actual.split(" ")
                for el in actual:
                    el=el.strip()
                    if el=='to':
                        ok=1
            if ok==1:
                for i in params:
                    actual=i
                    actual=actual.split(" ")
                    for el in actual:
                        el=el.strip()
                    removeFromTo(listTr,actual[0],actual[2])
            else:
                for i in params:
                    actual=i
                    actual=actual.split(" ")
                    for el in actual:
                        el=el.strip()
                    removeList(listTr,actual)
        elif action=='replace' and len(params)==5:
            listTr=replace(listTr,params)
        elif action=='add':
            for i in params:
                actual=i
                actual=actual.split(" ")
                for el in actual:
                    el=el.strip()
                value=actual[0]
                typeOf=actual[1]
                descr=actual[2]
                addTr(listTr,value,typeOf,descr)
        elif action=='insert' and len(params)==4:
            insertTr(listTr,params[0],params[1],params[2],params[3])
        else:
            print("Error: Invalid command!")
        
def checkAddTr(value,typeOf,descr):
    '''
    checks if the value is a positive number
    checks if the type is either IN or OUT
    checks if the description is valid(only text)
    '''
    if checkInteger(value):
        if typeOf=='in' or typeOf=='out':
            if descr.isalpha():
                return True
            else:
                print("Error: Please write a valid description!")
        else:
            print("Error: No other types of transactions are available, just IN and OUT!")
    else:
        print("Error: The first parameter must be an integer!")
    return False

def multipleAdd(params):
    parameters=[]
    actual=[]
    for param in params:
        if len(actual)==0:
           actual=param[:param.find(",")]
           actual+=param[param.find(","):]
        else:
            actual=param[param.find(actual)+1:param.find(",")]
            actual+=param[param.find(","):]
        add(parameters,actual)
    return parameters

def addTr(listTr,value,typeOf,descr):
    '''
    ex: add 100 out pizza – adds to the current day an out transaction of 100 RON with the “pizza”
description
    verifies the params with the checkAddTr function and if it is ok, adds sum to current day
    '''
    
    today=int(currentDay())
    if checkAddTr(value,typeOf,descr):
        newTr=(today,int(value),typeOf,descr)
        add(listTr,newTr)
        print("Transaction added succesfully!")       
        
def checkInsertTr(day,value,typeOf,descr):
    '''
    checks if the day is in [1,31]
    checks if the value is positive
    checks if the type is either IN or OUT
    '''
    if checkInteger(day):
        if validDay(int(day)):
            if checkInteger(value):
                if typeOf=='in' or typeOf=='out':
                    if descr.isalpha():
                        return True
                    else:
                        print("Error: Please write a valid description!")
                else:
                    print("Error: No other types of transactions are available, just IN and OUT!")
            else:
                print("Error: The second parameter must be an integer!")
        else:
            print("Error: You must insert something in the interval [1,31]!")
    else:
        print("Error: The first parameter must be an integer!")
    return False

def insertTr(listTr,day,value,typeOf,descr):
    '''
    insert 25 100 in salary – insert to day 25 an in transaction of 100 RON with the “salary”
description
    verifies the params withthe checkInsertTr function and if it is ok, adds transaction
to the current day
    '''
    if checkInsertTr(day,value,typeOf,descr):
        newTr=(int(day),int(value),typeOf,descr)
        add(listTr,newTr)
        print("Transaction added succesfully!")
        
def testAddTr():
    assert addTr(100,"in","hamburger")==True
    assert addTr(-230,"in","pizza")==False
    assert addTr(15,"between","juice")==False
    
def testInsertTr():
    assert insertTr(10,100,"in","pizza")==True
    assert insertTr(32,3000,"out","poker")==False
    assert insertTr(20,-100,"in","trip")==False
    assert insertTr(24,200,"hey","dontknow")==False

def testProgram():
    listTr=[]
    testInit(listTr)
    testAddTr()
    testInsertTr()

start()
