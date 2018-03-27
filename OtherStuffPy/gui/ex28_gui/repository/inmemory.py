from ex28_gui.domain.validators import StudentCRUDException

class RepositorException(StudentCRUDException):
    """
      Base class for the exceptions in the repository
    """
    def __init__(self, msg):
        self.__msg = msg
    def getMsg(self):
        return self.__msg
    def __str__(self):
        return self.__msg

class DuplicatedIDException(RepositorException):
    def __init__(self):
        RepositorException.__init__(self, "Duplicated ID")

class StudentRepository:
    """
      Class responsible for managing a list of students (store, retrieve , update, etc)
      GRASP - Pure Fabrication -  Repository Pattern
    """
    def __init__(self):
        self.__studs = {}

    def store(self, st):
        """
          Store a student
          st - student
          raise DuplicatedIDException for duplicated id
        """
        if st.getId() in self.__studs:
            raise DuplicatedIDException()
        self.__studs[st.getId()] = st

    def size(self):
        """
          return the number of students in the repository
        """
        return len(self.__studs)

    def remove(self, id):
        """
          remove a student from the repository
          id - string, the id of the student to be removed
          return student
          post: the repository not contains student with the given id
          raise ValueError if there is no student with the given id
        """
        if not id in self.__studs:
            raise ValueError("No student for the id:" + id)
        st = self.__studs[id]
        del self.__studs[id]
        return st
    def removeAll(self):
        """
          Remove all the students from the repository
        """
        self.__studs = {}

    def getAll(self):
        """
          Retrive all the students
          return a list with students
        """
        return self.__studs.values()

    def update(self, id, st):
        """
          Update student in the repository
          id - string, the id of the student to be updated
          st - Student, the updated student
          raise ValueError if there is no student with the given id
        """
        # remove the old student (this will raise exception if there is no student
        self.remove(id)
        # store the student
        self.store(st)

    def find(self, id):
        """
          Find the student for a given id
          id - string
          return student with the given id or None if there is no student with the given id
        """
        if not id in self.__studs:
            return None
        return self.__studs[id]


