import pickle
from Repository.RepositoryError import RepositoryError


class GenericFileRepository:

    def __init__(self, fileName):
        self.__storage = {}
        self.__fileName = fileName

    def __loadFromFile(self):
        try:
            with open(self.__fileName, 'rb') as f:
                self.__storage = pickle.load(f)
        except FileNotFoundError:
            self.__storage = {}

    def __saveToFile(self):
        with open(self.__fileName, 'wb') as f:
            pickle.dump(self.__storage, f)

    def create(self, entity):
        self.__loadFromFile()
        idEntity = entity.getIdEntity()
        if idEntity in self.__storage:
            raise RepositoryError("Id already exist!")
        self.__storage[idEntity] = entity
        self.__saveToFile()

    def read(self, idEntity=None):
        self.__loadFromFile()
        if idEntity is None:
            return self.__storage.values()
        if idEntity in self.__storage:
            return self.__storage[idEntity]
        return None

    def update(self, newEntity):
        self.__loadFromFile()
        idEntity = newEntity.getIdEntity()

        if idEntity not in self.__storage:
            raise RepositoryError("ID does not exist!")

        self.__storage[idEntity] = newEntity
        self.__saveToFile()

    def delete(self, idEntity):
        self.__loadFromFile()
        if idEntity not in self.__storage:
            raise RepositoryError("ID does not exist!")
        del self.__storage[idEntity]
        self.__saveToFile()

