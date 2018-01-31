n=int(input("Determine the palindrome of n = "))

def inverse(n):
    res=0
    digits=[]
    while n!=0:
        digits.append(int(n%10))
        n=int(n/10)
    for i in range(0,len(digits)):
        res=10*res+digits[i]
    return res
print("The palindrome is : ", inverse(n))
