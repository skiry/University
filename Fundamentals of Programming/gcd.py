def gcd(a,b):
    while a!=b:
        if a>b:
            a-=b
        else:
            b-=a
    return a
x=int(input("Enter x: "))
y=int(input("Enter y: "))
print("The greatest common divisor of" + str(x), " and y is ", gcd(x,y))
