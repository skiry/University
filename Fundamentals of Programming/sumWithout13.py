def sumWithout13(mylist):
    sum=0
    if mylist[0]!=13:
        sum+=mylist[0]
    index=1
    while index<len(mylist):
        if mylist[index]!=13 and mylist[index-1]!=13:
            sum+=mylist[index]
        index+=1
    return sum

def readlist():
    mylst=[]
    while True:
        x=int(input("Enter no. (-1 to stop)"))
        if x==-1:
            break
        mylst.append(x)
    return mylst

myl=readlist()
print("Their sum without the 13s and their neighbours is", sumWithout13(myl))
