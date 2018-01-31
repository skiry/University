from math import gcd

class UI:
    def __init__(self,funct):
        self.funct = funct
    def menu(self):
        text='''
            1. Print list
            2. Add a number
            3. Exit
            '''
        while True:
            print(text)
            cmd=int(input("Option: "))
            if cmd == 1:
                for i in self.funct.getAll():
                    print (str(i))
            elif cmd == 2:
                a=int(input("Enter nominator: "))
                b=int(input("Enter denominator: "))
                try:
                    self.funct.add(Rational(a,b))
                except ValueError:
                    print("Denominator must not be 0")
            elif cmd == 3:
                break
            else:
                print("Invalid option")
class Functions:
    def __init__(self):
        self.list = []
    def add(self,nr):
        self.list.append(nr)
    def getAll(self):
        return self.list
    
class Rational:
    def __init__(self,nom,denom=1):
        self.nom=nom
        self.denom=denom
        if denom==0:
            raise ValueError("Nominator must not be 0")
        Rational.simplify(self)
    def __str__(self):
        if self.denom==1:
            return str(self.nom)
        return str(self.nom)+'/'+str(self.denom)
    def simplify(self):
        cmmdc=gcd(self.nom,self.denom)
        self.nom//=cmmdc
        self.denom//=cmmdc

def testFunctions():
    f = Functions()
    x = Rational(1,2)
    y = Rational(2,3)
    assert f.getAll()==[]
    f.add(x)
    f.add(y)
    assert f.getAll()==[x,y]
    
def testRational():
    assert str(Rational(1,2))=="1/2"
    assert str(Rational(10,20))=="1/2"
    assert str(Rational(2,1))=="2"
    assert str(Rational(-3,4))=="-3/4"
    assert str(Rational(2))=="2"
    assert str(Rational(0,3))=="0"
    try:
        Rational(5,0)
        assert False
    except ValueError:
        assert True

f=Functions()
f.add(Rational(1,2))
UI=UI(f)
UI.menu()
testFunctions()
testRational()
q=Rational(1,2)
print(q)
