def verifperf(x):
    i=2
    while i*i<=x:
        if x%i==0:
            return False
        i+=1
    return True
def solve(n):
    if n<=0:
        n=1
    n+=1
    while verifperf(n)==False or verifperf(n+2)==False:
        n+=1
    return n

n=int(input("Determine the twin prime numbers(= two prime numbers p and q are called twin if q-p = 2) immediately larger than the given non-null natural number n = "))
n=solve(n)
print("The two prime numbers are ", n, " and " , n+2)

