n=int(input("Find the largest natural number m formed with the same digits of n = "))

def minimalno(n):
    res=0
    digits=[]
    for i in range(0,10):
        digits.append(0)
    while n!=0:
        digits[n%10]+=1
        n=int(n/10)
    for i in range(9,-1,-1):
        while digits[i]!=0:
            digits[i]-=1
            res=res*10+i
    return res
print("The largest number with the same digits is : ", minimalno(n))
