'''
Created on 14 nov. 2017

@author: Skiry
'''
from Class.Person import *
from Class.Activity import *

from Repository.ActivityRepository import *
from Repository.StudentRepository import *

from datetime import date,time

from Controller.StudentController import *
from Controller.ActivityController import *
from UI import *
from Repository import CSVStudentRepository
from Repository.CSVStudentRepository import CSVPersons
from Repository.CSVActivityRepository import CSVActivities
from Repository.BinaryStudentRepository import BinaryPersons
from Repository.BinaryActivityRepo import BinaryActivities
#from GUI import *
def testPerson():
    '''
    Test function for Person class
    '''
    test1 = Person(1,"John","0755241524","Iulius Street")
    assert test1.getId() == 1
    assert test1.getName() == "John"
    assert test1.getNumber() == "0755241524"
    assert test1.getAddress() == "Iulius Street"
    repo = StudentRepository()
    repo.add((1,"John","0755241524","Iulius Street"))
    repo.add((2,"Johnny","0755921000","Polus Street"))
    try:
        repo.get(3)
        assert False
    except studRepositoryException:
        assert True
    assert repo.get(1) == ('John','0755241524','Iulius Street')
    
def testActivity():
    '''
    Test functions for Activity class
    '''
    data = date(2017,7,11)
    timp = time(hour = 14, minute = 15)
    test1=Activity(1,2,data,timp,"Business Meeting")
    assert test1.getActId() == 1
    assert test1.getPersId() == 2
    assert test1.getDate() == "2017-07-11"
    assert test1.getTime() == "14:15"
    assert test1.getDescr() == "Business Meeting"
    repo = ActivityRepository()
    repo.add((1,2,date(2017,11,24),time(14,0),"pranz cu prietenii"))
    repo.add((2,2,date(2017,11,24),time(18,30),"cina cu prietenii"))
    try:
        repo.get(3)
        assert False
    except activityRepositoryException:
        assert True
    assert repo.get(1) == (2, '2017-11-24', '14:00', 'pranz cu prietenii')
    
def testProgram():  
    '''
    All the test functions will be performed here
    '''
    testPerson()
    testActivity()
    repo = StudentRepository()
    repo.add((1,"John","0755241524","Iulius Street"))
    repo.add((2,"Johnny","0755921000","Polus Street"))
    controller1 = StudentController(repo)
    try:
        controller1.add((3,"John","0955241529","Iulius Street"))
        print(str(controller1.getAll()))
        controller1.remove(2)
        print(str(controller1.getAll()))
        controller1.update((1,"Josh","0795241524","Iulius Street"))
        print(str(controller1.getAll()))
    except Exception as exc:
        print(exc)
    
    repo = ActivityRepository()
    repo.add((1,2,date(2017,11,24),time(14,0),"pranz cu prietenii"))
    repo.add((2,2,date(2017,11,24),time(18,30),"cina cu prietenii"))
    controller = ActivityController(repo)
    try:
        controller.add((3,2,date(2017,11,24),time(18,31),"cina cu familia"))
        print(str(controller.getAll()))
        controller.remove(2)
        print(str(controller.getAll()))
        controller.update((1,2,date(2017,11,24),time(14,0),"pranz cu dusmanii"))
        print(str(controller.getAll()))
    except Exception as exc:
        print(exc)
        
    ui = UI(controller1,controller)
    ui.menu() 

#testProgram()
def activityInit(test):
    test.add(Activity(1,2,date(2018,11,24),time(18,31),"mic dejun cu familia"))
    test.add(Activity(1,3,date(2018,11,24),time(18,31),"mic dejun cu familia"))
    test.add(Activity(2,5,date(2018,4,13),time(19,32),"pranz cu familia"))
    test.add(Activity(3,9,date(2018,9,10),time(18,33),"cina cu familia"))
    test.add(Activity(4,1,date(2018,2,28),time(7,34),"mic dejun cu prietenii"))
    test.add(Activity(5,10,date(2018,5,15),time(16,53),"pranz cu prietenii"))
    test.add(Activity(6,7,date(2018,11,30),time(15,36),"cina cu prietenii"))
    test.add(Activity(7,7,date(2018,10,4),time(4,37),"date cu prietena"))
    test.add(Activity(8,7,date(2018,3,21),time(3,35),"bowling cu baietii"))
    test.add(Activity(9,3,date(2018,6,14),time(2,1),"ziua bunicului"))
    test.add(Activity(10,2,date(2018,12,19),time(23,0),"interviu angajare"))
    test.add(Activity(11,96,date(2018,2,11),time(13,26),"mic dejun cu mama"))
    test.add(Activity(12,37,date(2018,1,5),time(21,4),"mic dejun cu tata"))
    test.add(Activity(13,36,date(2018,2,21),time(16,48),"mic dejun cu sora"))
    test.add(Activity(14,79,date(2018,2,27),time(13,48),"mic dejun cu fratele"))
    test.add(Activity(15,97,date(2018,2,9),time(8,50),"mic dejun cu bunicul"))
    test.add(Activity(16,56,date(2018,1,24),time(4,46),"mic dejun cu bunica"))
    test.add(Activity(17,94,date(2018,2,13),time(6,7),"mic dejun cu prietena"))
    test.add(Activity(18,16,date(2018,1,27),time(11,3),"mic dejun cu Gabi"))
    test.add(Activity(19,26,date(2018,1,5),time(2,51),"mic dejun cu colegul"))
    test.add(Activity(20,35,date(2018,2,4),time(2,43),"mic dejun cu seful"))
    test.add(Activity(21,12,date(2018,1,20),time(7,24),"pranz cu mama"))
    test.add(Activity(22,54,date(2018,2,2),time(3,15),"pranz cu tata"))
    test.add(Activity(23,17,date(2018,1,19),time(4,42),"pranz cu sora"))
    test.add(Activity(24,91,date(2018,1,23),time(5,48),"pranz cu fratele"))
    test.add(Activity(25,71,date(2018,2,18),time(11,54),"pranz cu bunicul"))
    test.add(Activity(26,11,date(2018,1,29),time(8,2),"pranz cu bunica"))
    test.add(Activity(27,19,date(2018,2,20),time(21,35),"pranz cu prietena"))
    test.add(Activity(28,95,date(2018,2,23),time(17,51),"pranz cu Gabi"))
    test.add(Activity(29,49,date(2018,1,20),time(5,8),"pranz cu colegul"))
    test.add(Activity(30,99,date(2018,1,4),time(16,51),"pranz cu seful"))
    test.add(Activity(31,70,date(2018,1,13),time(9,40),"cina cu mama"))
    test.add(Activity(32,60,date(2018,2,15),time(13,54),"cina cu tata"))
    test.add(Activity(33,63,date(2018,1,21),time(23,9),"cina cu sora"))
    test.add(Activity(34,21,date(2018,1,21),time(20,41),"cina cu fratele"))
    test.add(Activity(35,43,date(2018,1,1),time(16,4),"cina cu bunicul"))
    test.add(Activity(36,14,date(2018,2,19),time(9,19),"cina cu bunica"))
    test.add(Activity(37,86,date(2018,1,12),time(23,13),"cina cu prietena"))
    test.add(Activity(38,41,date(2018,2,6),time(19,26),"cina cu Gabi"))
    test.add(Activity(39,29,date(2018,1,4),time(1,41),"cina cu colegul"))
    test.add(Activity(40,77,date(2018,1,5),time(8,8),"cina cu seful"))
    test.add(Activity(41,44,date(2018,1,10),time(16,19),"intalnire cu mama"))
    test.add(Activity(42,78,date(2018,2,12),time(13,3),"intalnire cu tata"))
    test.add(Activity(43,62,date(2018,2,28),time(8,44),"intalnire cu sora"))
    test.add(Activity(44,31,date(2018,1,14),time(2,3),"intalnire cu fratele"))
    test.add(Activity(45,65,date(2018,1,14),time(12,10),"intalnire cu bunicul"))
    test.add(Activity(46,69,date(2018,2,28),time(22,11),"intalnire cu bunica"))
    test.add(Activity(47,80,date(2018,1,27),time(13,13),"intalnire cu prietena"))
    test.add(Activity(48,39,date(2018,2,23),time(8,40),"intalnire cu Gabi"))
    test.add(Activity(49,15,date(2018,2,27),time(5,3),"intalnire cu colegul"))
    test.add(Activity(50,25,date(2018,2,20),time(20,5),"intalnire cu seful"))
    test.add(Activity(51,98,date(2018,1,14),time(17,47),"jogging cu mama"))
    test.add(Activity(52,90,date(2018,1,11),time(6,54),"jogging cu tata"))
    test.add(Activity(53,46,date(2018,1,4),time(9,50),"jogging cu sora"))
    test.add(Activity(54,88,date(2018,2,28),time(17,15),"jogging cu fratele"))
    test.add(Activity(55,34,date(2018,2,27),time(23,50),"jogging cu bunicul"))
    test.add(Activity(56,55,date(2018,2,26),time(19,22),"jogging cu bunica"))
    test.add(Activity(57,64,date(2018,2,19),time(14,0),"jogging cu prietena"))
    test.add(Activity(58,75,date(2018,1,21),time(4,23),"jogging cu Gabi"))
    test.add(Activity(59,38,date(2018,2,28),time(11,32),"jogging cu colegul"))
    test.add(Activity(60,76,date(2018,2,22),time(3,39),"jogging cu seful"))
    test.add(Activity(61,27,date(2018,1,18),time(2,18),"sa suni pe mama"))
    test.add(Activity(62,28,date(2018,1,21),time(18,27),"sa suni pe tata"))
    test.add(Activity(63,45,date(2018,2,16),time(9,1),"sa suni pe sora"))
    test.add(Activity(64,23,date(2018,2,25),time(3,0),"sa suni pe fratele"))
    test.add(Activity(65,72,date(2018,1,15),time(12,44),"sa suni pe bunicul"))
    test.add(Activity(66,20,date(2018,2,28),time(11,2),"sa suni pe bunica"))
    test.add(Activity(67,93,date(2018,2,17),time(19,19),"sa suni pe prietena"))
    test.add(Activity(68,81,date(2018,1,12),time(4,28),"sa suni pe Gabi"))
    test.add(Activity(69,89,date(2018,1,15),time(2,15),"sa suni pe colegul"))
    test.add(Activity(70,50,date(2018,2,24),time(7,42),"sa suni pe seful"))
    test.add(Activity(71,67,date(2018,1,15),time(8,53),"sa iei de la munca pe mama"))
    test.add(Activity(72,82,date(2018,2,26),time(20,25),"sa iei de la munca pe tata"))
    test.add(Activity(73,48,date(2018,2,28),time(21,42),"sa iei de la munca pe sora"))
    test.add(Activity(74,61,date(2018,1,26),time(21,20),"sa iei de la munca pe fratele"))
    test.add(Activity(75,52,date(2018,2,22),time(14,23),"sa iei de la munca pe bunicul"))
    test.add(Activity(76,92,date(2018,1,11),time(17,1),"sa iei de la munca pe bunica"))
    test.add(Activity(77,66,date(2018,1,29),time(12,36),"sa iei de la munca pe prietena"))
    test.add(Activity(78,85,date(2018,1,2),time(16,34),"sa iei de la munca pe Gabi"))
    test.add(Activity(79,40,date(2018,1,5),time(4,36),"sa iei de la munca pe colegul"))
    test.add(Activity(80,74,date(2018,1,19),time(17,43),"sa iei de la munca pe seful"))
    test.add(Activity(81,99,date(2018,1,13),time(12,19),"sa ajuti pe mama"))
    test.add(Activity(82,33,date(2018,2,4),time(13,23),"sa ajuti pe tata"))
    test.add(Activity(83,22,date(2018,2,20),time(8,44),"sa ajuti pe sora"))
    test.add(Activity(84,100,date(2018,2,21),time(16,16),"sa ajuti pe fratele"))
    test.add(Activity(85,59,date(2018,2,24),time(13,14),"sa ajuti pe bunicul"))
    test.add(Activity(86,73,date(2018,2,1),time(9,36),"sa ajuti pe bunica"))
    test.add(Activity(87,58,date(2018,1,20),time(12,43),"sa ajuti pe prietena"))
    test.add(Activity(88,13,date(2018,1,5),time(22,20),"sa ajuti pe Gabi"))
    test.add(Activity(89,42,date(2018,1,2),time(22,4),"sa ajuti pe colegul"))
    test.add(Activity(90,18,date(2018,1,26),time(5,36),"sa ajuti pe seful"))
    test.add(Activity(91,30,date(2018,2,3),time(6,23),"sa ii dai un mesaj la mama"))
    test.add(Activity(92,47,date(2018,2,8),time(5,59),"sa ii dai un mesaj la tata"))
    test.add(Activity(93,24,date(2018,1,5),time(3,29),"sa ii dai un mesaj la sora"))
    test.add(Activity(94,84,date(2018,1,6),time(14,23),"sa ii dai un mesaj la fratele"))
    test.add(Activity(95,83,date(2018,2,24),time(2,49),"sa ii dai un mesaj la bunicul"))
    test.add(Activity(96,57,date(2018,2,16),time(5,19),"sa ii dai un mesaj la bunica"))
    test.add(Activity(97,53,date(2018,2,21),time(15,29),"sa ii dai un mesaj la prietena"))
    test.add(Activity(98,87,date(2018,2,18),time(12,38),"sa ii dai un mesaj la Gabi"))
    test.add(Activity(99,32,date(2018,2,28),time(8,27),"sa ii dai un mesaj la colegul"))
    test.add(Activity(100,51,date(2018,1,22),time(13,18),"sa ii dai un mesaj la seful"))

def personInit(pers):
    pers.add(Person(1,"John","0755241524","Iulius Street"))
    pers.add(Person(2,"Johny","0756712000","Polus Street"))
    pers.add(Person(3,"Johnn","0755292845","Bucharest Street"))
    pers.add(Person(4,"Johnny","0234525024","Cluj Street"))
    pers.add(Person(5,"Jonathan","0755255000","London Street"))
    pers.add(Person(6,"Jonathany","0712009581","Carls Street"))
    pers.add(Person(7,"Jonathann","0234000111","Paris Street"))
    pers.add(Person(8,"Jonathanny","0747991223","Louis Street"))
    pers.add(Person(9,"Johannis","0722345116","Vuitton Street"))
    pers.add(Person(10,"Johannatanys","0763990113","Gucci Street"))
    pers.add(Person(11,"Gabi Popescu","0655390915","North Avenue"))
    pers.add(Person(12,"Gabriela Andronic","0655576693","Ridge Road"))
    pers.add(Person(13,"Maria Botor","0655730020","Lantern Lane"))
    pers.add(Person(14,"Paul Popescu","0655007479","Edgewood Road"))
    pers.add(Person(15,"Cosmin Vonea","0655160421","Route 70"))
    pers.add(Person(16,"Mihai Gabor","0655277949","Berkshire Drive"))
    pers.add(Person(17,"Maria Rusu","0655462381","Hawthorne Avenue"))
    pers.add(Person(18,"Gabi Andronic","0655899335","Cottage Street"))
    pers.add(Person(19,"Andrei Botor","0655756045","River Street"))
    pers.add(Person(20,"Vicky Tanase","0655861361","Market Street"))
    pers.add(Person(21,"Gabriela Rusu","0655633247","Cemetery Road"))
    pers.add(Person(22,"Andreea Popescu","0655045956","Jefferson Court"))
    pers.add(Person(23,"Andreea Dumitrescu","0655515081","Henry Street"))
    pers.add(Person(24,"Vlad Vonea","0655122290","Willow Street"))
    pers.add(Person(25,"Andreea Bejenaru","0655037331","Broad StreetMain Street North"))
    pers.add(Person(26,"Gabriela Vonea","0655777660","Lake Street"))
    pers.add(Person(27,"Mihai Tanase","0655990732","New Street"))
    pers.add(Person(28,"Mihai Botor","0655338066","William Street"))
    pers.add(Person(29,"Vicky Dumitrescu","0655156871","Cherry Lane"))
    pers.add(Person(30,"Cosmin Dumitrescu","0655644902","Cypress Court"))
    pers.add(Person(31,"Mihai Vonea","0655327475","Union Street"))
    pers.add(Person(32,"Cosmin Rusu","0655030212","Locust Street"))
    pers.add(Person(33,"Vicky Vonea","0655791361","Sherman Street"))
    pers.add(Person(34,"Gabriela Botor","0655709542","Old York Road"))
    pers.add(Person(35,"Vlad Mare","0655919581","Country Club Drive"))
    pers.add(Person(36,"Andrei Tanase","0655060315","Franklin Street"))
    pers.add(Person(37,"Gabi Botor","0655389945","Hamilton Street"))
    pers.add(Person(38,"Andreea Gabor","0655998019","Catherine Street"))
    pers.add(Person(39,"Mihai Mare","0655600373","Maple Street"))
    pers.add(Person(40,"Vlad Rusu","0655820014","3rd Avenue"))
    pers.add(Person(41,"Maria Vonea","0655964206","8th Avenue"))
    pers.add(Person(42,"Vlad Bejenaru","0655211884","Holly Court"))
    pers.add(Person(43,"Mihai Dumitrescu","0755390915","7th Avenue"))
    pers.add(Person(44,"Maria Bejenaru","0455390915","High Street"))
    pers.add(Person(45,"Andrei Vonea","0555390915","Linden Street"))
    pers.add(Person(46,"Gabriela Bejenaru","0855390915","4th Street South"))
    pers.add(Person(47,"Andreea Andronic","0755576693","Route 17"))
    pers.add(Person(48,"Gabi Rusu","0455576693","Cobblestone Court"))
    pers.add(Person(49,"Gabi Dumitrescu","0555576693","York Road"))
    pers.add(Person(50,"Vicky Botor","0855576693","Pennsylvania Avenue"))
    pers.add(Person(51,"Paul Mare","0755730020","Bridge Street"))
    pers.add(Person(52,"Andreea Tanase","0455730020","Devon Court"))
    pers.add(Person(53,"Paul Andronic","0555730020","Elm Avenue"))
    pers.add(Person(54,"Paul Tanase","0855730020","2nd Street West"))
    pers.add(Person(55,"Mihai Popescu","0755007479","Oxford Road"))
    pers.add(Person(56,"Gabi Tanase","0455007479","Lexington Drive"))
    pers.add(Person(57,"Vicky Popescu","0555007479","Oak Street"))
    pers.add(Person(58,"Cosmin Tanase","0855007479","West Avenue"))
    pers.add(Person(59,"Maria Mare","0755160421","Tanglewood Drive"))
    pers.add(Person(60,"Paul Dumitrescu","0455160421","11th Street"))
    pers.add(Person(61,"Andreea Botor","0555160421","Sherwood Driv"))
    pers.add(Person(62,"Vicky Mare","0855160421","Clinton Street"))
    pers.add(Person(63,"Mihai Andronic","0755277949","Arlington Avenue"))
    pers.add(Person(64,"Vlad Gabor","0455277949","Victoria Court"))
    pers.add(Person(65,"Vlad Popescu","0555277949","3rd Street"))
    pers.add(Person(66,"Gabriela Mare","0855277949","Edgewood Drive"))
    pers.add(Person(67,"Maria Andronic","0755462381","Somerset Drive"))
    pers.add(Person(68,"Cosmin Popescu","0455462381","Belmont Avenue"))
    pers.add(Person(69,"Vlad Botor","0555462381","Meadow Street"))
    pers.add(Person(70,"Vlad Dumitrescu","0855462381","5th Street West"))
    pers.add(Person(71,"Andrei Dumitrescu","0755899335","Washington Avenue"))
    pers.add(Person(72,"Andreea Mare","0455899335","Orchard Avenue"))
    pers.add(Person(73,"Andrei Bejenaru","0555899335","Williams Street"))
    pers.add(Person(74,"Gabriela Gabor","0855899335","Canterbury Road"))
    pers.add(Person(75,"Andrei Andronic","0755756045","Orange Street"))
    pers.add(Person(76,"Paul Gabor","0455756045","Windsor Drive"))
    pers.add(Person(77,"Andreea Rusu","0555756045","Willow Avenue"))
    pers.add(Person(78,"Gabi Gabor","0855756045","Cambridge Road"))
    pers.add(Person(79,"Cosmin Botor","0755861361","Grove Avenue"))
    pers.add(Person(80,"Andrei Mare","0455861361","Laurel Lane"))
    pers.add(Person(81,"Vlad Tanase","0555861361","Fairview Road"))
    pers.add(Person(82,"Paul Rusu","0855861361","Valley View Road"))
    pers.add(Person(83,"Cosmin Andronic","0755633247","Woodland Road"))
    pers.add(Person(84,"Andrei Gabor","0455633247","King Street"))
    pers.add(Person(85,"Maria Dumitrescu","0555633247","Columbia Street"))
    pers.add(Person(86,"Gabriela Tanase","0855633247","Hickory Street"))
    pers.add(Person(87,"Andrei Rusu","0755045956","1st Street"))
    pers.add(Person(88,"Vicky Andronic","0455045956","College Avenue"))
    pers.add(Person(89,"Vicky Rusu","0555045956","Walnut Avenue"))
    pers.add(Person(90,"Gabriela Popescu","0855045956","East Street"))
    pers.add(Person(91,"Mihai Bejenaru","0755515081","Prospect Street"))
    pers.add(Person(92,"Vicky Gabor","0455515081","Sycamore Drive"))
    pers.add(Person(93,"Cosmin Bejenaru","0555515081","Euclid Avenue"))
    pers.add(Person(94,"Gabi Bejenaru","0855515081","Harrison Avenue"))
    pers.add(Person(95,"Paul Bejenaru","0755122290","Wall Street"))
    pers.add(Person(96,"Cosmin Mare","0455122290","Virginia Street"))
    pers.add(Person(97,"Maria Gabor","0555122290","Summit Street"))
    pers.add(Person(98,"Paul Vonea","0855122290","Carriage Drive"))
    pers.add(Person(99,"Gabi Vonea","0755037331","Cleveland Street"))
    pers.add(Person(100,"Maria Popescu","0455037331","Rose Street"))

SETTINGS_FILE = "settings.properties"

def readSettings():
    '''
    Reads the program's settings file
    output:
        A dictionary containing the program settings
    '''
    f = open(SETTINGS_FILE, "r")
    lines = f.read().split('\n')
    settings = {}
    
    for line in lines:
        setting = line.split("=")
        if len(setting) > 1:
            settings[setting[0]] = setting[1]    
    f.close()
    return settings

settings = readSettings()

if settings['repository'] == 'inmemory':
    test = ActivityRepository()
    pers = StudentRepository()
    personInit(pers)
    activityInit(test)
elif settings['repository'] == 'CSV':
    test = CSVActivities(settings['activities'])
    pers = CSVPersons(settings['persons'])
elif settings['repository'] == 'binary':
    '''
    test1 = ActivityRepository()
    activityInit(test1)
    interm = StudentRepository()
    personInit(interm)
    '''
    test = BinaryActivities(settings['activities'])
    pers = BinaryPersons(settings['persons'])
    '''
    for c in interm.getAll():
       pers.add(interm.getAll()[c])
    for c in test1.getAll():
        for j in test1.getAll()[c]:
            test.add(j)
    '''
undoCtrl = UndoController()
ctrl = ActivityController(test,undoCtrl,pers)
contr = StudentController(pers,undoCtrl)

if settings['ui'] == 'ui':
    ui = UI(contr,ctrl,undoCtrl)
    ui.menu()
elif settings['ui'] == 'gui':
    #ui = GUI(contr,ctrl,undoCtrl)
    ui.menu()


'''
            SQL SELECT *
            CASCADE DELETE+ when u undo a remove of act multiple times,it fucks up+remove pers, why not removed?
            AS 9
            AS 10
            binary files? read/write like in txt files?
'''