def readlist(listt):
    print("Give a list of integers")
    listt=[int(x) for x in input().split()]
    return listt
def printlist(listt):
    print("Your list has the following elements: ")
    print(listt)
def uimenu():
    print("1. Read a list of integers!")
    print("2. Print the list!")
    print("3. Print the longest sequence such that consecutive numbers have different signs!")
    print("4. Print the longest sequence such that all consecutive numbers pairs have at least 2 common digits!")
    print("5. Print the longest sequence such that the sum of its elements is 10!")
    print("6. Print the longest sequence that is in the form of the mountain!")
    print("7. Exit the program!")
def solve3(listt):
    maxx=0
    inc=0
    actlen=0
    for i in range(0,len(listt)-1):
        if ((listt[i]<0 and listt[i+1]>0) or (listt[i]>0 and listt[i+1]<0)):
            actlen+=1
        elif actlen >= maxx:
            maxx=actlen
            inc=i-maxx
            actlen=0
    if actlen >= maxx:
        maxx=actlen
        inc=len(listt)-1-maxx
    if maxx==0:
        return "There is no such sequence"
    else:
        return listt[inc:inc+maxx+1]
def verifydigits(a,b):
    a=abs(a)
    b=abs(b)
    digits=[]
    counter=0
    for i in range(0,10):
        digits.append(0)
    while a!=0:
        digits[a%10]=1
        a=int(a/10)
    while b!=0:
        if digits[b%10]==1:
            counter+=1
            digits[b%10]=0
        b=int(b/10)
    if counter>=2:
        return True
    return False
def solve4(listt):
    maxx=0
    inc=0
    actlen=0
    for i in range(0,len(listt)-1):
        if verifydigits(listt[i],listt[i+1]) is True:
            actlen+=1
        elif actlen >= maxx:
            maxx=actlen
            inc=i-maxx
            actlen=0
    if actlen >= maxx:
        maxx=actlen
        inc=len(listt)-1-maxx
    if maxx==0:
        return "There is no such sequence"
    else:
        return listt[inc:inc+maxx+1]
def solve5(listt):
    maxx=0
    inc=0
    for i in range(0,len(listt)-1):
        summ=listt[i]
        k=i+1
        while k< len(listt):
            summ+=listt[k]
            if summ==10:
                if maxx<k-i:
                    maxx=k-i
                    inc=i
                print(inc)
                print(summ)
            k+=1
    if maxx!=0:
        return listt[inc:inc+maxx+1]
    else:
        return "There is no such sequence"
def solve6(listt):
    maxx=0
    inc=0
    actlen=0
    for i in range(0,len(listt)-1):
        k=i
        ok=1
        while k<len(listt)-1 and listt[k+1]>listt[k]:
            k+=1
            ok=3
        if ok==3:
            while k<len(listt)-1 and listt[k+1]<listt[k]:
                k+=1
                ok=5
        if k-i>=maxx and ok==5:
            maxx=k-i
            inc=i
    if maxx!=0:
        return listt[inc:inc+maxx+1]
    return "There is no such sequence"
"""   if actlen==0:
            print(i,"s")
            if listt[i+1]>listt[i]:
                actlen=1
                i+=1
        if listt[i+1]>listt[i] and listt[i]>listt[i-1]:
            actlen+=1
        elif listt[i+1]<listt[i] and listt[i]>listt[i-1]:
            actlen+=1
            ok=1
        elif listt[i+1]<listt[i] and listt[i]<listt[i-1]:
            if ok==1:
                actlen+=1
        else:
            print(listt[i])
            if actlen>=maxx:
                maxx=actlen
                inc=i-maxx+1
            print(i)
            print(maxx)
            actlen=0
            ok=0
    return listt[inc:inc+maxx]
"""
def start():
    ok=1
    while True:
        uimenu()
        x=input()
        if x=="1":
            mylist=[]
            mylist=readlist(mylist)
            ok=0
        elif x=="2":
            if ok==0:
                printlist(mylist)
            else:
                print("Error: You do not have a valid list!")
        elif x=="3":
            if ok==0:
                print("The longest sequence such that consecutive numbers have different signs:")
                print(solve3(mylist))
            else:
                print("Error: You do not have a valid list!")
        elif x=="4":
            if ok==0:
                print("The longest sequence such that all consecutive numbers pairs have at least 2 common digits:")
                print(solve4(mylist))
            else:
                print("Error: You do not have a valid list!")
        elif x=="5":
            if ok==0:
                print("The longest sequence such that the sum of its elements is 10:")
                print(solve5(mylist))
            else:
                print("Error: You do not have a valid list!")
        elif x=="6":
            if ok==0:
                print("The longest sequence that is in the form of the mountain:")
                print(solve6(mylist))
            else:
                print("Error: You do not have a valid list!")
        elif x=="7":
            break
        else:
           print("Error")
start()


