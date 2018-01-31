year=int(input("Enter a year and the numbers of days in that year and i will show the month and the day of that year. Year : "))
day=int(input("Days : "))
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
    global day
    if testleap(year)==True:
        months[1]=29
    for i in range(0,12):
        test=day-months[i]
        if test>=0:
            day-=months[i]
        else :
            return i+1
            break

old=computeage()
print("year = ", year)
print("month = ", old)
print("day = ", day)
