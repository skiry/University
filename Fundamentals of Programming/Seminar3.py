def printStudents(sList):
    print(sList)
def findById(sList,idd):
    for i in range(0,len(sList)):
        if sList[i][0]==idd:
            return i
    return -1
def testInit(listt):
    listt.append(("1","Mary",8))
    listt.append(("2","Marhya",9))
    listt.append(("3","Mara",6))
    listt.append(("4","Myrya",10))
def testFindById():
    sList=[]
    testInit(sList)
    
    assert findById(sList,'3')==2
    assert findById(sList,'69')==-1
def addStudent(listt,stud):
    if findById(listt,stud[0])==-1:
        listt.append(stud)
        return True
    return False
def testAddStudent():
    sList=[]
    testInit(sList)

    assert addStudent(sList,("5","Mary",8))==True
    assert addStudent(sList,("1","Mary",9))==False
def addStudentCmd(sList,params):
    if len(params)!=3:
        print("Error")
        return False
    if addStudent(sList,(params[0],params[1],params[2])):
        return True
    return False
def addCommand():
    cmd=input("your command:")
    if cmd.find(" ") is -1:
        '''
        the user requested help
        '''
        command=cmd
        params=""
    else:
        command=cmd[:cmd.find(" ")]
        params=cmd[cmd.find(" "):]
        params=params.split(",")
        for i in range(0,len(params)):
            params[i]=params[i].strip()
    return (command,params)
def deleteId(sList,index):
    index=index.strip()
    for stud in sList:
        if str(stud[0])==str(index):
            return stud
    return False
def menu():
    sList=[]
    testInit(sList)
    menuis='''
            add <id>,<name>,<grade>
            del <id>
            show all
            help
            exit
            '''
    while True:
        cmd=addCommand()
        if cmd[0] == 'help':
            print(menuis)
        elif cmd[0] == "add":
            if addStudentCmd(sList,(cmd[1][0],cmd[1][1],cmd[1][2])):
                print(cmd[1][1]," added succesfully!")
            else:
                print(cmd[1][1]," has not been added!")
        elif cmd[0] == "del":
            here=deleteId(sList,cmd[1][0])
            if here:
                print(here[1]," has been deleted from the list!")
                sList.remove(here)
            else:
                print("The id ", cmd[1][0]," is inexistent!")
        elif cmd[0] == "show":
            print(sList)
        elif cmd[0] == "exit":
            break
        else:
            print("Error!")
testFindById()
testAddStudent()
menu()
