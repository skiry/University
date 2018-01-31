def addStudent(sList, Student):
    if checkId(sList, Student[0]):
        sList.append(Student)
        return True
    return False

def checkId(sList, Id):
    for i in range (0, len(sList)):
        if sList[i][0] == Id:
            return False
    return True

def readStudent():
    Id = input("give the student's id: ")
    name = input("give the student's name: ")
    grade = int(input("give the student's grade: "))
    return (Id, name, grade)

def printMenu():
    print("1. add a student")
    print("2. delete a student")
    print("3. show the students with the grade greater than a giver number")
    print("4. end the program")
    
def studExists(sList,index):
    for i in sList:
        if str(i[0])==str(index):
            return i
    return False

def delStudent(sList,index):
    exist=studExists(sList,index)
    if exist:
        sList.remove(exist)
    else:
        print("The student with this index is inexistent!")

def showStudents(sList,grad):
    for i in sList:
        if str(i[2])>=str(grad) or str(i[2])=="10":
            print(i)
def start():
    sList = []
    while True:
        printMenu()
        a=input()
        print(sList)
        if a=="1":
            Student = readStudent()
            if addStudent(sList, Student):
                print("Student added succesfully")
            else:
                print("error while adding student")
        elif a=="2":
            index=int(input("Delete student with id = "))
            delStudent(sList,index)
        elif a=="3":
            grad=int(input("Minimum grade = "))
            showStudents(sList,grad)
        elif a=="4":
            break
        else:
            print("error")

start()
