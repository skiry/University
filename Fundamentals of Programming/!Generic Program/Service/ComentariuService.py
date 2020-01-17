from Domain.Comentariu import Comentariu
from Service.ServiceError import ServiceError

class ComentariuService:

    def __init__(self, comentariuRepository, stireRepository):
        self.__comentariurepository = comentariuRepository
        self.__stireRepository = stireRepository

    def __idStireExista(self, idStire):
        stiri = self.__stireRepository.read()
        for stire in stiri:
            if stire.getIdEntity() == idStire:
                return True
        return False

    def __validIdComentariuParinte(self, idComentariuParinte):
        comentarii = self.getAll()
        for comentariu in comentarii:
            if comentariu.getIdEntity() == idComentariuParinte:
                return True
        return False


    def addComentariu(self, id, idStire, idComentariuParinte, continut):
        if not self.__idStireExista(idStire):
            raise ServiceError("Id Stire nu exista! ")
        if idComentariuParinte != 0:
            if not self.__validIdComentariuParinte(idComentariuParinte):
                raise ServiceError("Id Comentariu parinte nu exista! ")
        else:
            idComentariuParinte = None
        comentariu = Comentariu(id, idStire, idComentariuParinte, continut)
        self.__comentariurepository.create(comentariu)

    def getAll(self):
        return self.__comentariurepository.read()

    def __numarulDeCuvinteDinContinutulStirilor(self):
        stiri = self.__stireRepository.read()
        dictionar = {}
        for stire in stiri:
            lungimeContinut = len(stire.getContinut().split())
            dictionar[stire.getIdEntity()] = lungimeContinut
        return dictionar

    def ordonareComentariiDupaNumarulDeCuvinteDinContinu(self):
        comentarii = self.getAll()
        continutStiri = self.__numarulDeCuvinteDinContinutulStirilor()
        comentariiSortate = sorted(comentarii, key=lambda x: continutStiri[x.getIdEntity()], reverse=True)
        tuplu = []
        for s in comentariiSortate:
            t = [s, continutStiri[s.getIdStire()]]
            tuplu.append(t)
        return tuplu

