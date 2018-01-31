n=int(input("Enter a number n, then the first prime number larger than n will be generated : "))

def verprime(x):
    d=2
    isPrime=True
    while isPrime==True and d*d<=x:
        if x%d==0:
            isPrime=False
        d+=1
    return isPrime

n+=1
while verprime(n)==False:
    n+=1
print("The first prime number larger than n is ", n)
