from Repository.RepositoryError import RepositoryError
from Service.ServiceError import ServiceError


class Console:
    def __init__(self, stireService, comentariuService):
        self.__stireService = stireService
        self.__comentariuService = comentariuService

    @staticmethod
    def __printMenu():
        """
        Afiseaza meniul principal
        :return:
        """
        print("0. Iesire\n"
              "1. Add Stire \n"
              "2. Add Comentariu \n"
              "3. Generare n stiri \n"
              "4. Afisare comentarii ordonate crescator dupa numarul de cuvinte din continut \n"
              "5. Afisarea tututor comentariilor radacina impreuna cu numarul de subcomentarii \n"
              "a. Afisare \n")

    def __handleStiretAdd(self):
        try:
            id = int(input("ID: "))
            titlu = input("Titlu: ")
            continut = input("Continu :")
            autor = input("Autor: ")
            self.__stireService.addStire(id, titlu, continut, autor)
            print('Stirea a fost adaugat!')
        except RepositoryError as error:
            print(error)
        except ValueError as error:
            print(error)

    def __handleComentariuAdd(self):
        try:
            id = int(input("ID: "))
            idStire = int(input("ID Stire: "))
            idComentariuParinte = int(input("ID comentariu parinte: ") or 0)
            continut = input("Continut: ")
            self.__comentariuService.addComentariu(id, idStire, idComentariuParinte, continut)
        except RepositoryError as error:
            print(error)
        except ServiceError as error:
            print(error)
        except ValueError as error:
            print(error)

    def __handleGenerareStiri(self):
        try:
            lenght = int(input("Introduceti numarul de stiri pe care doriti sa le generati automat: "))
            whatID = int(input("Introduceti id-ul de la care doriti sa inceapa generarea stirilor: "))
            self.__stireService.generareStiri(lenght, whatID)
        except ValueError as error:
            print(error)

    def __handleOrdonareComentariiDupaContinut(self):
        comentariiSortate = self.__comentariuService.ordonareComentariiDupaNumarulDeCuvinteDinContinu()
        for comentariu in comentariiSortate:
            com1 = comentariu[0]
            com2 = comentariu[1]
            print(str(com1) + " ----- " + str(com2))

    def runConsole(self):
        self.__showList(self.__stireService.getAll())
        self.__showList(self.__comentariuService.getAll())
        while True:
            self.__printMenu()
            operation = input("Optiune: ")
            if operation == '1':
                self.__handleStiretAdd()
            elif operation == '2':
                self.__handleComentariuAdd()
            elif operation == '3':
                self.__handleGenerareStiri()
            elif operation == '4':
                self.__handleOrdonareComentariiDupaContinut()
            elif operation == '5':
                continue
            elif operation == 'a':
                self.__showList(self.__stireService.getAll())
                self.__showList(self.__comentariuService.getAll())
            elif operation == '0':
                return
            else:
                print("Optiune gresita")

    @staticmethod
    def __showList(objects):
        """
        Afiseaza o lista de obiecte de tip Medicament, Tranzactie, CardClient
        :param objects:
        :return:
        """
        for _object in objects:
            print(_object)
