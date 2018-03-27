'''
Created on 4 dec. 2017

@author: Skiry
'''
from random import random, sample, randrange
class Person:
    def __init__(self, personId, familyName, givenName):
        self.__personId = personId
        self.__familyName = familyName
        self.__givenName = givenName
    
    def getId(self):
        return self.__personId
    
    def getFamilyName(self):
        return self.__familyName
    
    def getGivenName(self):
        return self.__givenName
    
    def __str__(self):
        return str(self.__personId) + " -- " + self.__familyName + " " + self.__givenName
    
def writeToFile(fileName, persons):
    f = open(fileName, "w")
    try:
        for p in persons:
            pString = str(p.getId()) + ";" + p.getFamilyName() + ";" + p.getGivenName() + "\n"
            f.write(pString)
        f.close()
    except Exception as e:
        print("An error occured -" + str(e))

def readFile(fileName):
    result = []
    try:
        f = open(fileName, "r")
        line = f.readline().strip()
        while  len(line) > 0:
            line = line.split(";")
            result.append(Person(int(line[0]), line[1], line[2]))
            line = f.readline().strip()
        f.close()
    except IOError as e:
        """
            Here we 'log' the error, and throw it to the outer layers 
        """
        print("An error occured - " + str(e))
        raise e

    return result

"""
    Initialize a list of objects
"""
persons = [Person(1, "Popica", "Anca"), Person(2, "Morariu", "Sergiu"), Person(3, "Moldovean", "Iuliu")]

"""
    Write it to a text file
"""
writeToFile("persons.txt", persons)

"""
    Read it back and see what we have
"""
for p in readFile("persons.txt"):
    print(p)

ids = []
idsNormal = []
for i in range(11,101):
    ids.append(i)
    idsNormal.append(i)
nume = ["Andrei","Mihai","Cosmin","Vlad","Gabi","Paul","Andreea","Maria","Gabriela","Vicky"]
prenume = ["Popescu","Rusu","Gabor","Andronic","Mare","Botor","Vonea","Tanase","Dumitrescu","Bejenaru"]
numeprenume = []
for i in range(0,10):
    for j in range(0,10):
        if i != j:
            numeprenume.append(str(nume[i])+" "+str(prenume[j]))
ids = sample(ids,len(ids))
numeprenume=sample(numeprenume,len(numeprenume))
streets = 'North Avenue,Ridge Road,Lantern Lane,Edgewood Road,Route 70,Berkshire Drive,Hawthorne Avenue,Cottage Street,River Street,Market Street,Cemetery Road,Jefferson Court,Henry Street,Willow Street,Broad StreetMain Street North,Lake Street,New Street,William Street,Cherry Lane,Cypress Court,Union Street,Locust Street,Sherman Street,Old York Road,Country Club Drive,Franklin Street,Hamilton Street,Catherine Street,Maple Street,3rd Avenue,8th Avenue,Holly Court,7th Avenue,High Street,Linden Street,4th Street South,Route 17,Cobblestone Court,York Road,Pennsylvania Avenue,Bridge Street,Devon Court,Elm Avenue,2nd Street West,Oxford Road,Lexington Drive,Oak Street,West Avenue,Tanglewood Drive,11th Street,Sherwood Driv,Clinton Street,Arlington Avenue,Victoria Court,3rd Street,Edgewood Drive,Somerset Drive,Belmont Avenue,Meadow Street,5th Street West,Washington Avenue,Orchard Avenue,Williams Street,Canterbury Road,Orange Street,Windsor Drive,Willow Avenue,Cambridge Road,Grove Avenue,Laurel Lane,Fairview Road,Valley View Road,Woodland Road,King Street,Columbia Street,Hickory Street,1st Street,College Avenue,Walnut Avenue,East Street,Prospect Street,Sycamore Drive,Euclid Avenue,Harrison Avenue,Wall Street,Virginia Street,Summit Street,Carriage Drive,Cleveland Street,Rose Street,Route 1,Ivy Lane,Hawthorne Lane,Park Street,River Road,George Street,Broadway,6th Avenue,Glenwood Avenue'
streets=streets.split(',')
print(len(streets))
phone = """06 55 390 915
06 55 576 693
06 55 730 020
06 55 007 479
06 55 160 421
06 55 277 949
06 55 462 381
06 55 899 335
06 55 756 045
06 55 861 361
06 55 633 247
06 55 045 956
06 55 515 081
06 55 122 290
06 55 037 331
06 55 777 660
06 55 990 732
06 55 338 066
06 55 156 871
06 55 644 902
06 55 327 475
06 55 030 212
06 55 791 361
06 55 709 542
06 55 919 581
06 55 060 315
06 55 389 945
06 55 998 019
06 55 600 373
06 55 820 014
06 55 964 206
06 55 211 884"""
phone = phone.split('\n')
phone2 = []
phone3 = []
phone4 = []
phone5 = []
activitati1 = ["mic dejun cu ","pranz cu ","cina cu ","intalnire cu ","jogging cu ","sa suni pe ","sa iei de la munca pe ","sa ajuti pe ","sa ii dai un mesaj la "]
activitati2 = ["mama","tata","sora","fratele","bunicul","bunica","prietena","Gabi","colegul","seful"]
activitati = []
for i in activitati1:
    for j in activitati2:
        activitati.append(str(i)+str(j))
for i in range(0,len(phone)):
    phone[i]=str(phone[i][0:2])+str(phone[i][3:5])+str(phone[i][6:9])+str(phone[i][10:13])
    phone2.append(str(phone[i][0:1])+"7"+str(phone[i][2:10]))
    phone3.append(str(phone[i][0:1])+"4"+str(phone[i][2:10]))
    phone4.append(str(phone[i][0:1])+"5"+str(phone[i][2:10]))
    phone5.append(str(phone[i][0:1])+"8"+str(phone[i][2:10]))
for i in range(0,len(phone)):
    phone.append(phone2[i])
    phone.append(phone3[i])
    phone.append(phone4[i])
    phone.append(phone5[i])
for i in phone:
    print(i)
for i in range(0,90):
    print(str(idsNormal[i])+';"'+str(numeprenume[i])+'";"'+str(phone[i])+'";"'+str(streets[i])+'"')