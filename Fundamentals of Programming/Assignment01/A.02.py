n=int(input("Given the natural number n, determine the prime numbers p1 and p2 such that n = p1 + p2. N = "))

def checkprime(x):
    for d in range(2,int(x/2)):
        if x%d==0:
            return False
    return True

def solve(x):
    for i in range(2,int(x/2)):
        if checkprime(i)==True and checkprime(x-i)==True:
            return i
    return 0

p1=solve(n)
if p1!=0:
    print("The prime numbers are : " , p1 , " + " , n-p1 , " = " , n)
else:
    print("The number you have chosen cannot be splitted in two prime numbers!")
    
