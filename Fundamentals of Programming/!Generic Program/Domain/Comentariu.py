from Domain.Entity import Entity


class Comentariu(Entity):
    def __init__(self, id, idStire, idComentariuParinte, continut):
        super().__init__(id)
        self.__idStire = idStire
        self.__idComentariuParinte = idComentariuParinte
        self.__continut = continut

    def getIdStire(self):
        return self.__idStire
        
    def __str__(self):
        return "Comentariu: {}, {}, {}, {}".format(self.getIdEntity(), self.__idStire, self.__idComentariuParinte, self.__continut)
