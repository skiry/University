'''
John wants to manage his bank account. In order to complete this task, John needs an application to
store, for a given month, all the bank transactions performed on his account. Each transaction is
stored in the application using the following elements:
*day (of the month in which the transaction was made, between 0 and 30)
*amount of money (that was transferred, positive integer)
*type (in - into the account, out – from the account)
*description
'''
#### get() functions
### commit@scs.ubbcluj.ro .zip


import userInterface
import functions
import time
print("Hi. What kind of UI would you like to use? ")
time.sleep(1)
print("Command-based",end="")
time.sleep(0.5)
print(" or ",end="")
time.sleep(0.5)
print("Menu-based?")
functions.testProgram()
while True:
    cmd=input()
    cmd=cmd.split("-")
    for i in range(0,len(cmd)):
        cmd[i]=cmd[i].strip()
    if cmd[0]=='menu' or cmd[0]=='Menu':
        userInterface.start(1)
        break
    elif cmd[0]=='command' or cmd[0]=='Command':
        userInterface.start(0)
        break
    else:
        print("Please be careful!")



















        
'''
1.add <value> <type> <description>
        2.insert <day> <value> <type> <description>

        3.remove <day>
        4.remove <start day> to <end day>
        5.remove <type>
        6.replace <day> <type> <description> with <value>

        7.list
        8.list <type>
        9.list [ < | = | > ] <value>
        10.list balance <day>

        11.sum <type>
        12.max <type> <day>

        13.filter <type>
        14.filter <type> <value>

        15.undo
        16.exit


        '''






