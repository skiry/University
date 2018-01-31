n=int(input("Consider a given natural number n. Determine the product p of all the proper factors of n = "))

def product(x):
    prod=1
    for i in range(2,int(x/2)+1):
        if x%i==0:
            prod*=i
    return prod

print("The product of all the proper factors of ", n ," is " + str(product(n)))
