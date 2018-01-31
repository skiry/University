'''
manageRationalNumers

    -add number
    -delete at index
    -sum between indices:with gcd
    -multiple undo

'''
from copy import deepcopy
from functools import reduce

def gcd(a,b):
    if a==0:
        return b
    elif a>0 and b>0:
        while a!=b:
            if a>b:
                a-=b
            else:
                b-=a
    return a
def menu():
    text="""1.Add number
            2.Delete at index
            3. Sum between indices
            4. Undo
            5. Exit
            """
    print(text)
    rez=input()
    return rez

def addNumber(myList,a,b):
    try:
        a=int(a)
        b=int(b)
    except:
        print("Insert integers!")
        return 
    if b==0:
        print("denominator must be non 0")
    else:
        myList.append((a,b))

def deleteNumber(myList,index):
    if index.isdigit():
        index = int(index)
        if index>0 and index<=len(myList):
            myList.remove(myList[index-1])

def sum(myList,a,b):
    if a.isdigit() and b.isdigit():
        a=int(a)
        b=int(b)
        if a>0 and b>0 and a<=len(myList) and b<=len(myList) and a<=b:
            res = reduce(lambda x, y: [x[0] * y[1] + x[1] * y[0], x[1] * y[1]], myList[a-1:b])
            x=gcd(res[0],res[1])
            res[0]=res[0]/x
            res[1]=res[1]/x
            return (int(res[0]),int(res[1]))
    return False
def main():
    myList=[]
    undoList=[]
    while True:
        print(myList)
        rez=int(menu())
        if rez==5:
            break
        elif rez==4:
            if len(undoList)>0:
                myList=undoList[len(undoList)-1]
                undoList.pop(len(undoList)-1)
        elif rez==1:
            undoList.append(deepcopy(myList))
            a=input("Insert nominator:")
            b=input("Insert denominator:")
            addNumber(myList,a,b)
        elif rez==2:
            undoList.append(deepcopy(myList))
            index=input("Index: ")
            deleteNumber(myList,index)
        elif rez==3:
            a=input("Index 1: ")
            b=input("Index 2: ")
            res=sum(myList,a,b)
            if res:
                if int(res[1])==1:
                    print(int(res[0]))
                else:
                    print(int(res[0]),"/",int(res[1]))
def testAdd():
    myList=[(1,3),(2,3),(1,1),(5,5)]
    el = ['1', '4']
    l = len(myList)

    addNumber(myList, el[0], el[1])
    
    assert l + 1 == len(myList)
def testDeleteNumber():
    myList=[(1,3),(2,3),(1,1),(5,5)]
    index='2'
    l=len(myList)

    deleteNumber(myList,index)

    assert l-1==len(myList)
def testSum():
    myList=[(1,3),(2,3),(1,1),(5,5)]
    a='1'
    b='2'
    assert sum(myList,a,b)==(1.0,1.0)
testAdd()
testDeleteNumber()
testSum()
main() 
