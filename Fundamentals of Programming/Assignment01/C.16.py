n=int(input("Generate the largest perfect number(= a number is perfect if it is equal to the sum of its divisors, except itself) smaller than a given natural number n = "))
initial=n
def verifperf(x):
    sum=0
    for i in range(1,int(x/2)+1):
        if x%i==0:
            sum+=i
    if sum==x:
        return True
    return False

n-=1
while verifperf(n)==False:
    n-=1
if n!=0:
    print("The largest perfect number smaller than ", initial, " is " , n)
else:
    print("Such a number does not exist!")
