n=int(input("Find the smallest Fibonacci number larger than a given natural number n = "))
initial=n
def verifperf(x):
    a=0
    b=1
    c=0
    while b<=x:
        c=a+b
        a=b
        b=c
    return b

print("The smallest Fibonacci number larger than ", initial, " is " , verifperf(n))

