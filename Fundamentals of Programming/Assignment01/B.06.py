year=int(input("I am gonna compute your age in number of days. Your year : "))
month=int(input("And your month : "))
day=int(input("Day : "))
age=0
import datetime
actual=datetime.datetime.now()
months=[]
def assigndays():
    months.append(31)
    months.append(28)
    months.append(31)
    months.append(30)
    months.append(31)
    months.append(30)
    months.append(31)
    months.append(31)
    months.append(30)
    months.append(31)
    months.append(30)
    months.append(31)
    
def testleap(x):
    if x%4==0 and x%100!=0:
        return True
    elif x%400==0:
        return True
    return False

def computeage():
    assigndays()
    if testleap(year)==True:
        months[1]=29

    age=months[month-1]-day
    for i in range(month+1,12):
        age+=months[i]

    for i in range(year+1,2017):
        if testleap(i)==True:
            age+=366
        else:
            age+=365
    for i in range(0,actual.month):
        age+=months[i]
    age+=actual.day
    return age

old=computeage()
print("You are " , old , " days old!")
