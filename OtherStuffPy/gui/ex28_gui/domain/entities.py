class Address:
    """
      Represent an address
    """
    def __init__(self, street, nr, city):
        self.__street = street
        self.__nr = nr
        self.__city = city

    def getStreet(self):
        return self.__street

    def getNr(self):
        return self.__nr

    def getCity(self):
        return self.__city

    def __str__(self):
        """
          Give a string representation for the address
          return string
        """
        return self.__street+" nr."+self.__nr+" "+self.__city

class Student:
    """
      Represent a student
    """
    def __init__(self, id, name, adr):
        """
         Create a new student
         id, name String
         address - Address
        """
        self.__id = id
        self.__name = name
        self.__adr = adr

    def getId(self):
        """
          Getter method for id
        """
        return self.__id

    def getName(self):
        """
          Getter for name
        """
        return self.__name

    def getAdr(self):
        """
         Getter for address
        """
        return self.__adr
    def __str__(self):
        """
          Give a string representation for the student
          return string
        """
        return self.__id+" "+self.__name+" "+str(self.__adr)

    def __eq__(self, ot):
        """
          Define equal for students
          ot - student
          return True if ot and the current instance represent the same student
        """
        return self.__id==ot.__id