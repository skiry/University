def listcreator(adg,bdg):   
    for i in range(0,10):
        adg.append(0)
        bdg.append(0)
def frecv(p,lst):
    while p!=0:
        lst[p%10]+=1
        p=int(p/10)
def solve():    
    frecv(p1,adg)
    frecv(p2,bdg)
    isTrue=True
    for i in range(0,10):
        if adg[i]!=0 and bdg[i]==0:
            isTrue = False
        elif adg[i]==0 and bdg[i]!=0:
            isTrue = False
    return isTrue
def final():
    if solve()==False:
        print(p1 , " and " , p2 , " have different digits, so they do not have the property P")
    else:
        print(p1 , " and " , p2 , " have the same digits, so they have the property P")

print("The numbers n1 and n2 have the property P if their writings in basis 10 have the same digits (e.g. 2113 and 323121). Determine whether two given natural numbers have the property P.")
p1=int(input("N1 = "))
p2=int(input("N2 = "))
adg=[]
bdg=[]
listcreator(adg,bdg)
final()
