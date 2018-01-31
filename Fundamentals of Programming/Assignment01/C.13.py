def checkPrime(x):
    for i in range(2,x//2+1):
        if x%i==0:
            return False
    return True
def verprime(x,n):
    global now
    initial=now
    for i in range(2,int(x/2)+1):
        if x%i==0 and checkPrime(i):
            if now+1==n:
                return i
            else:
                now+=1
    if initial is now:
        now+=1
    if now==n: return x
    return 0
def solve(x):
    global now
    for i in range(2,x):
        value=verprime(i,x)
        if value!=0:
            return value

print("Determine the n-th element of the sequence 1,2,3,2,5,2,3,7,2,3,2,5,... obtained from the sequence of natural numbers by replacing composed numbers with their prime divisors")
n=int(input("N = "))
now=1
if n==1:
    print("1")
else:
    print(solve(n))
