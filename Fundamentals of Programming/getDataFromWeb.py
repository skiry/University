from urllib.request import *
from time import *

f="http://10.5.4.196:5000/"
link=urlopen(f)
file=int(link.read())
print("Wait 35 seconds!")
free=ocup=0
for i in range(10):
    link=urlopen(f)
    file=int(link.read())
    if file:
        ocup+=1
        print("Sala este ocupata")
    else:
        free+=1
        print("Sala este libera")
    sleep(3.5)
if free>(ocup+free)/2:
    print("The room is free!")
else:
    print("This room is ocuppied!")
