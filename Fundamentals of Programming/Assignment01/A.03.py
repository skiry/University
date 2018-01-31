n=int(input("Find the minimal natural number m formed with the same digits of n = "))

def minimalno(n):
    res=0
    digits=[]
    for i in range(0,10):
        digits.append(0)
    while n!=0:
        digits[n%10]+=1
        n=int(n/10)
    while digits[1]!=0:
        digits[1]-=1
        res=10*res+1
    while digits[0]!=0:
        digits[0]-=1
        res*=10
    for i in range(2,10):
        while digits[i]!=0:
            digits[i]-=1
            res=res*10+i
    return res
print("The minimal number with the same digits is : ", minimalno(n))
