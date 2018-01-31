def verifperf(x):
    sum=0
    for i in range(1,int(x/2)+1):
        if x%i==0:
            sum+=i
    if sum==x:
        return True
    return False

def solve(n):  
    n+=1
    while verifperf(n)==False:
        n+=1
    if n==0:
        return 6
    return n
        
n=int(input("Generate the smallest perfect number(= a number is perfect if it is equal to the sum of its divisors, except itself) larger than a given natural number n = "))
n=solve(n)
print("The largest perfect number smaller than n is " , n)
