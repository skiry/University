from Domain.Entity import Entity


class Stire(Entity):
    def __init__(self, id, titlu, continut, autor):
        super().__init__(id)
        self.__titlu = titlu
        self.__continut = continut
        self.__autor = autor

    def getTitlu(self):
        return self.__titlu

    def getContinut(self):
        return self.__continut

    def __str__(self):
        return "Stire: {}, {}, {},Lungime Continut: {}, {}".format(self.getIdEntity(), self.__titlu, self.__continut,
                                                                   len(self.__continut.split()), self.__autor)
