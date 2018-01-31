def verifperf(x):
    i=2
    while i*i<=x:
        if x%i==0:
            return False
        i+=1
    return True

def solve(n):
    n-=1
    while verifperf(n)==False:
        n-=1
    return n

def final():
    if n>1:
        print("The largest prime number smaller than n is " , n)
    else:
        print("Such a number does not exist!")
    
n=int(input("Generate the largest prime number smaller than a given natural number n = "))
n=solve(n)
final()
