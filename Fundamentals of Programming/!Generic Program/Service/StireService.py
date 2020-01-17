from Domain.Stire import Stire


class StireService:

    def __init__(self, stireRepository):
        self.__stireRepository = stireRepository

    def addStire(self, id, titlu, continut, autor):
        stire = Stire(id, titlu, continut, autor)
        self.__stireRepository.create(stire)

    def getAll(self):
        return self.__stireRepository.read()

    def generareStiri(self, lenght, whatID):
        from random import choice, randint
        from string import ascii_uppercase, ascii_lowercase
        id = whatID
        for stire in range(lenght):
            id += 1
            titlu = ''.join(choice(ascii_lowercase) for i in range(randint(3, 10)))
            continut = ''
            for _cuvant in range(randint(5, 15)):
                cuvant = ''.join(choice(ascii_lowercase) for i in range(randint(2, 10)))
                continut = continut + ' ' + cuvant
            autor = ''.join(choice(ascii_uppercase) for i in range(randint(4, 8)))
            self.addStire(id, titlu, continut, autor)


