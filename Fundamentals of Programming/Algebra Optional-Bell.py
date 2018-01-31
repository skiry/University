print("Hello! Insert a positive number and I will compute the number of all the partitions of the set A={1,2,...,n}. Also, if I can, I compute all the partitions (0 to exit): ")
rez=[]
def printUI():
    n=input("n= ")
    while ver(n)==False:
        n=input("Please insert a positive number!")
    return int(n)

def ver(n):
    if n.isdigit() and int(n)>=0:
        return True
    return False

def Bell(n):
    if n==1:
        return 1
    l1=[]
    l2=[]
    for i in range(n):
        l1.append(0)
        l2.append(0)
    l1[0]=1
    l1[1]=2
    x=2
    while x<n:
        x+=1
        if x%2:
            l2[0]=l1[x-2]
            for i in range(1,x):
                l2[i]=l2[i-1]+l1[i-1]
        else:
            l1[0]=l2[x-2]
            for i in range(1,x):
                l1[i]=l1[i-1]+l2[i-1]
    if n%2:
        return l2[n-1]
    else:
        return l1[n-1]
    
def maxim(k):
    maxOf=0
    for i in range(1,k+1):
        if rez[i]>=maxOf:
            maxOf=rez[i]
    return maxOf

def afis(n):
    x=0
    pos=0
    print("The partition is:")
    for i in range(1,maxim(n)+1):  
        print("{",end="")
        for j in range(1,n+1):
            if rez[j]==i:
                print(j,end="")
        print("}",end=" ")
    print()
    print("The equivalence relations are:")
    for i in range(1,maxim(n)+1):
        for j in range(1,n+1):
            if rez[j]==i:
                for k in range(1,n+1):
                    if rez[k]==i:
                        print("(",j,",",k,")",end=" ")
    print()
                    
    
                   
def partitions(poz,n):
    global rez
    for i in range(1,maxim(poz-1)+2):
        rez[poz]=i
        if poz==n:
            afis(n)
        else:
            partitions(poz+1,n)

def start():
    while True:
        n=printUI()
        if n==0:
            print("Thank you! Have a great day!")
            return False
        for i in range(1,n+2):
            rez.append(0)
        if n<=10:
            partitions(1,n)
        number=Bell(n)
        print("The number of all partitions and equivalence relations is: ",number)    
        
start()


