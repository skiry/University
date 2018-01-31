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

def findAct(a):
    if a=='1':
        return 'add'
    elif a=='2':
        return 'insert'
    elif a=='3' or a=='4' or a=='5':
        return 'remove'
    elif a=='6':
        return 'replace'
    elif a=='7' or a=='8' or a=='9' or a=='10':
        return 'list'
    elif a=='11':
        return 'sum'
    elif a=='12':
        return 'max'
    elif a=='13' or a=='14':
        return 'filter'
    elif a=='15':
        return 'undo'
    elif a=='16':
        return 'exit'
    return ''

def goWith(a):
    if a=='1':
        value=input("Value: ")
        typeOf=input("Type: ")
        description=input("Descripion: ")
        return (value,typeOf,description)
    elif a=='2':
        day=input("Day: ")
        value=input("Value: ")
        typeOf=input("Type: ")
        description=input("Descripion: ")
        return (day,value,typeOf,description)
    elif a=='3':
        day=input("Day: ")
        return[day]
    elif a=='4':
        day=input("From day: ")
        to=input("To day: ")
        return[day,'to',to]
    elif a=='5':
        typeOf=input("IN or OUT: ")
        return[typeOf]
    elif a=='6':
        day=input("Day: ")
        typeOf=input("Type: ")
        description=input("Descripion: ")
        value=input("With value: ")
        return (day,typeOf,description,'with',value)
    elif a=='8':
        typeOf=input("IN or OUT: ")
        return[typeOf]
    elif a=='9':
        sign=input("Symbol ('>=<'): ")
        value=input("Value: ")
        return [sign,value]
    elif a=='10':
        day=input("Balance on day: ")
        return ['balance',day]
    elif a=='11':
        typeOf=input("IN or OUT: ")
        return[typeOf]
    elif a=='12':
        typeOf=input("IN or OUT: ")
        day=input("Day: ")
        return(typeOf,day)
    elif a=='13':
        typeOf=input("IN or OUT: ")
        return[typeOf]
    elif a=='14':
        typeOf=input("IN or OUT: ")
        value=input("Value: ")
        return(typeOf,value)
    return ()

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
        params=""
    else:
        command=cmd[:cmd.find(" ")]
        params=cmd[cmd.find(" ")+1:]
        params=params.split(",")
        for i in range(0,len(params)):
            params[i]=params[i].split()
            for j in range(0,len(params[i])):
                params[i][j]=params[i][j].strip()
        
    return (command,params)

def checkParam(param):
    '''
    checks if the sent parameter is either IN or OUT
    '''
    if param=='in' or param=='out':
        return True
    return False

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

def maxOnDay(listTr,typeOf,day):
    '''
    max out 15 – write the maximum out transaction on day 15.
    with proper checkings
    '''
    maxim=0
    zi=tip=0
    if checkParam(typeOf):
        if checkInteger(day) and validDay(int(day)):
            for i in listTr:
                if int(i[0])==int(day):
                    zi=1
                    if i[2]==typeOf:
                        tip=1
                        if maxim<i[1]:
                            maxim=i[1]
            if zi==0:
                return -1
            elif zi and tip==0:
                return -2
            else:
                return maxim
        else:
            return -3
    else:
        return -4

def filterList(listTr,param):
    '''
    filters transactions
    filter in – keep only in transactions.
    filter in 100 – keep only in transactions having an amount of money smaller than 100 RON.
    '''
    ok=0
    if len(param)==2:
        value=param[1]
        if checkInteger(value):
            ok=1
            maxValue=int(value)
    elif len(param)==1:
        maxValue=9999999999999999999999999999999999999
    typeOf=param[0]
    if checkParam(typeOf):
        removed=0
        ok=2
        for i in reversed(listTr):
            if i[2]!=typeOf:
                removed=1
                listTr.remove(i)
            elif int(i[1])>=maxValue:
                removed=1
                listTr.remove(i)
    if len(param)==0 or len(param)>2:
        return -2
    else:
        if ok==0:
            return -3
        elif ok==1:
            return -4
    if removed:
        return -5
    else:
        return -6
    return listTr
    
def sumIO(listTr,param):
    '''
    checks for the good running of the function
    sum in– write the total amount from in transactions
    '''
    mySum=0
    if checkParam(param):
        for i in listTr:
            if i[2]==param:
                mySum+=i[1]
        if mySum:
            return mySum
        return -1
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

def removeList(listTr,param):
    '''
    checks what to remove: day, in transactions or out transactions
    prints nice texts
    '''
    if checkInteger(param):
        if validDay(int(param)):
            if removeDay(listTr,int(param)):
                return True
            else:
                return 2
        else:
            return 3
    elif param=='in' or param=='out':
        if removeSymbol(listTr,param):
            return True
        else:
            return 2
    return 4
    
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
                            return 2
                    else:
                        return 3
                else:
                    return 4
            else:
                return 5
        else:
            return 6
    else:
        return 7
        
def replace(listTr,params):
    '''
    replace 12 in salary with 2000 – replace the amount for the in transaction having the “salary”
description from day 12 with 2000 RON
    '''
    from copy import deepcopy
    okList=[]
    change=0
    if validReplace(listTr,params)==True:
        for el in listTr:
            if el[0]==int(params[0]) and el[2]==params[1] and el[3]==params[2]: 
                mytuple=(el[0],int(params[4]),el[2],el[3])
                el=deepcopy(mytuple)
                change=1
            add(okList,el)
        if change:
            return okList
    return listTr


def removeFromTo(listTr,fromDay,toDay):
    '''
    removes all transactions between two given days
    remove 5 to 10 – removes all transactions between day 5 and day 10.

    '''
    if checkInteger(fromDay) and validDay(int(fromDay)) and validDay(int(toDay)) and checkInteger(toDay):
        for elements in reversed(listTr):
            if elements[0]>=int(fromDay) and elements[0]<=int(toDay):
                listTr.remove(elements)
        return True
    else:
        return False

def currentDay():
    '''
    this functions returns the current day of the month"
    '''
    import time
    day=time.strftime("%d")
    return day

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
                return 2
        else:
            return 3
    else:
        return 4

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
                        return 2
                else:
                    return 3
            else:
                return 4
        else:
            return 5
    else:
        return 6

def addTr(listTr,param):
    '''
    ex: add 100 out pizza – adds to the current day an out transaction of 100 RON with the “pizza”
description
    verifies the params with the checkAddTr function and if it is ok, adds sum to current day
    '''
    
    value=param[0]
    typeOf=param[1]
    descr=param[2]
    today=int(currentDay())
    if len(param)==3:
        rez=checkAddTr(value,typeOf,descr)
        if rez==True:
            newTr=(today,int(value),typeOf,descr)
            add(listTr,newTr)
        return rez
    return False
    

def insertTr(listTr,day,value,typeOf,descr):
    '''
    insert 25 100 in salary – insert to day 25 an in transaction of 100 RON with the “salary”
description
    verifies the params withthe checkInsertTr function and if it is ok, adds transaction
to the current day
    '''
    rez=checkInsertTr(day,value,typeOf,descr)
    if rez==True:
        newTr=(int(day),int(value),typeOf,descr)
        add(listTr,newTr)
    return rez
    

def testAddTr():
    listTr=[]
    param=(100,"in","hamburger")
    assert addTr(listTr,param)==True
    param=(-230,"in","pizza")
    assert addTr(listTr,param)!=True
    param=(15,"between","juice")
    assert addTr(listTr,param)!=True
    
def testInsertTr():
    myList=[]
    assert insertTr(myList,10,100,"in","pizza")==True
    assert insertTr(myList,32,3000,"out","poker")!=True
    assert insertTr(myList,20,-100,"in","trip")!=True
    assert insertTr(myList,24,200,"hey","dontknow")!=True

def testRemoveFromTo():
    myList=[]
    testInit(myList)
    assert removeFromTo(myList,10,20)==True
    assert removeFromTo(myList,1,32)==False
    assert removeFromTo(myList,1,-32)==False
    assert removeFromTo(myList,"a",5)==False

def testReplace():
    listTr=[]
    testInit(listTr)
    param=('20', 'in', 'lottery', 'with', '2000')
    assert validReplace(listTr,param)==True
    param=('20', 'in', 'lottery', 'for', '2000')
    assert validReplace(listTr,param)!=True
    param=('20', 'in', 'lottery', 'with', '-2000')
    assert validReplace(listTr,param)!=True

def testCheckParam():
    assert checkParam('in')==True
    assert checkParam('out')==True
    assert checkParam('test')==False

def testCheckSymbol():
    assert checkSymbol('<')==1
    assert checkSymbol('=')==2
    assert checkSymbol('>')==3
    assert checkSymbol('test')==False

def testRemoveSymbol():
    listTr=[]
    testInit(listTr)
    assert removeSymbol(listTr,'in')==True
    assert removeSymbol(listTr,'test')==False
    
def testRemoveDay():
    listTr=[]
    testInit(listTr)
    assert removeDay(listTr,1)==True
    assert removeDay(listTr,300)==False

def testMaxOnDay():
    listTr=[]
    testInit(listTr)
    assert maxOnDay(listTr,'in','20')==100
    assert maxOnDay(listTr,'out','20')==-2
    assert maxOnDay(listTr,'in','19')==-1

def testValidDay():
    assert validDay(1)==True
    assert validDay(20)==True
    assert validDay(-1)==False
    assert validDay(32)==False

def testBalance():
    listTr=[]
    testInit(listTr)
    assert balance(listTr,1)==-10
    assert balance(listTr,40)==False
    assert balance(listTr,2)==-110

def testRemoveDay():
    listTr=[]
    testInit(listTr)
    assert removeDay(listTr,7)==True
    assert removeDay(listTr,7)==False

def testRemoveSymbol():
    listTr=[]
    testInit(listTr)
    assert removeSymbol(listTr,'in')==True
    assert removeSymbol(listTr,'in')==False
    
def testProgram():
    listTr=[]
    testInit(listTr)
    testAddTr()
    testInsertTr()
    testRemoveFromTo()
    testReplace()
    testCheckParam()
    testCheckSymbol()
    testRemoveSymbol()
    testRemoveDay()
    testMaxOnDay()
    testValidDay()
    testBalance()
    testRemoveDay()
    testRemoveSymbol()
