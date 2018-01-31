from functions import *
from copy import deepcopy
menuBased='''
        1.add <value> <type> <description>
        2.insert <day> <value> <type> <description>

        3.remove <day>
        4.remove <start day> to <end day>
        5.remove <type>
        6.replace <day> <type> <description> with <value>

        7.list
        8.list <type>
        9.list [ < | = | > ] <value>
        10.list balance <day>

        11.sum <type>
        12.max <type> <day>

        13.filter <type>
        14.filter <type> <value>

        15.undo
        16.exit
        '''
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

        sum <type>
        max <type> <day>

        filter <type>
        filter <type> <value>

        undo
        '''
    print(menu)
    
def printList(listTr):
    '''
    prints the entire list of transactions line by line
    '''
    for trans in listTr:
        print (trans)

def printListInOut(listTr,param):
    '''
    lists all the IN or OUT transactions
    ex : list in – write all the in transactions.
    '''
    if checkParam(param):
        for element in listTr:
            if element[2]==param:
                print (element)
    else:
        print("Error: You must require IN or OUT transactions!")


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
        
def printAdd(truth):
    if truth==True:
        print("Transaction added succesfully!")
    elif truth==2:
        print("Error: Please write a valid description!")
    elif truth==3:
        print("Error: No other types of transactions are available, just IN and OUT!")
    elif truth==4:
        print("Error: The first parameter must be an integer!")
    else:
        print("Three parameters please...")
        
def printInsert(truth):
    if truth==True:
        print("Transaction added succesfully!")
    elif truth==2:
        print("Error: Please write a valid description!")
    elif truth==3:
        print("Error: No other types of transactions are available, just IN and OUT!")
    elif truth==4:
        print("Error: The second parameter must be an integer!")
    elif truth==5:
        print("Error: You must insert something in the interval [1,31]!")
    elif truth==6:
        print("Error: The first parameter must be an integer!")

def printRemoveFromTo(truth):
    if truth==True:
        print("Everything was deleted as you wished!")
    else:
        print("Error: Something is not good. Call help()")

def printReplace(truth):
    if truth==True:
        print("No type errors!")
    elif truth==2:
        print("Error: You must replace this transaction with an integer value!")
    elif truth==3:
        print("....WITH...write WITH!!!")
    elif truth==4:
        print("Error: Please write a valid description!")
    elif truth==5:
        print("Error: No other types of transactions are available, just IN and OUT!")
    elif truth==6:
        print("Error: You must replace something in the interval [1,31]!")
    elif truth==7:
        print("Error: The first parameter must be an integer!")

def printReplace2(list1,list2):
    if list1==list2:
        print("No replacement!")
    else:
        print("Replacement OK!")

def printRemoveList(truth):
    if truth==True:
        print("Transactions removed!")
    elif truth==2:
        print("There are no transactions like those you wanted to remove...")
    elif truth==3:
        print("When you will be in this day of the month, call me!")
    elif truth==4:
        print("Error: What do you want to remove? Pay attention!")

def printSumIO(truth):
    if truth==-1:
        print("There are no transactions like those!")
    elif truth==False:
        print("Error: Request IN or OUT sum please.")
    else:
        print(truth)

def printMaxOnDay(truth):
    if truth==-1:
        print("There is no transaction on this day!")
    elif truth==-2:
        print("There are no transactions like those on this day!")
    elif truth==-3:
        print("Day parameter must be 1<=...<=31")
    elif truth==-4:
        print("IN or OUT")
    else:
        print("The maximum is :",truth)

def printFilterList(truth,listTr):
    if truth==-2:
        print("Error: Invalid Command!")
    elif truth==-3:
        print("The first parameter must be IN or OUT!")
    elif truth==-4:
        print("The second parameter must be an integer!")
    elif truth==-5:
        print("All done!")
    elif truth==-6:
        print("Everything is the same!")
    else:
        listTr=deepcopy(truth)

def start(kind):
    '''
    the start of the program
    '''
    listTr=[]
    testInit(listTr)
    undo=[]
    while True:
        if kind==0:
            cmd=getCommand()
            action=cmd[0]
            params=cmd[1]
        else:
            print(menuBased)
            action=input()
            if action!='15' and action!= '16'and action!= '7':
                params=[[]]
                params[0]=goWith(action)
            else:
                params=[]
            action=findAct(action)
        err=0
        if len(params)==0:
            '''
            if the length of the parameters is 0, then we have only one word(=command)
            the only possibilities: exit,help,list,undo. anything else leads to errors!
            '''
            if action=='exit':
                print("Have a great day!")
                break
            elif action=='help':
                helpMe()
            elif action=='list':
                printList(listTr)
            elif action=='undo':
                if(len(undo)>0):
                    listTr=deepcopy(undo[len(undo)-1])
                    undo.pop(len(undo)-1)
                    print("Undo OK!")
                else:
                    print("You cannot undo anymore!")
            else:
                err=1
        elif len(params)==1:
            '''
            if the length of the parameters is 1, we have only a set of parameters
            '''
            param=params[0]
            if action=='add' and len(param)==3:
                add(undo,deepcopy(listTr))
                printAdd(addTr(listTr,param))
            elif action=='remove' and len(param)==1:
                add(undo,deepcopy(listTr))
                printRemoveList(removeList(listTr,param[0]))
            elif action=='remove' and len(param)==3:
                add(undo,deepcopy(listTr))
                printRemoveFromTo(removeFromTo(listTr,param[0],param[2]))
            elif action=='insert' and len(param)==4:
                add(undo,deepcopy(listTr))
                printInsert(insertTr(listTr,param[0],param[1],param[2],param[3]))  
            elif action=='list' and len(param)==1:
                printListInOut(listTr,param[0])
            elif action=='list'and len(param)==2 and str(param[0])==str('balance'):
                printBalance(listTr,param[1])
            elif action=='list' and len(param)==2:
                printListSEG(listTr,param)
            elif action=='replace' and len(param)==5:
                add(undo,deepcopy(listTr))
                printReplace(validReplace(listTr,param))
                forTest=deepcopy(listTr)
                listTr=replace(listTr,param)
                printReplace2(forTest,listTr)                    
            elif action=='sum' and len(param)==1:
                printSumIO(sumIO(listTr,param[0]))
            elif action=='max' and len(param)==2:
                printMaxOnDay(maxOnDay(listTr,param[0],param[1]))
            elif action=='filter':
                add(undo,deepcopy(listTr))
                res=filterList(listTr,param)
                printFilterList(res,listTr)  
            else:
                err=1
        elif len(params)>1:
            '''
            if the length of the parameters is greater than 1, then the user can insert multiple data delimited by a comma
            '''
            if action=='add':
                add(undo,deepcopy(listTr))
                for i in range(0,len(params)):
                    actual=params[i]
                    printAdd(addTr(listTr,actual))
            elif action=='remove':
                add(undo,deepcopy(listTr))
                for i in range(0,len(params)):
                    param=params[i]
                    if len(param)==1:
                        printRemoveList(removeList(listTr,param[0]))
                    elif len(param)==3:
                        printRemoveFromTo(removeFromTo(listTr,param[0],param[2]))
            else:           
                err=1
        if err:
            print("Error: Invalid command!")
