from ex28_gui.domain.entities import Student, Address

class StudentController:
    """
      Class responsible with the use cases related to Student CRUD
      GRASP Controller
    """
    def __init__(self, val, repo):
        """
          Initialise the controller,
          controller need a validator and a repository to perform the operations
          val - StudentValidator (injected)
          repo - StudentRepository (injected
        """
        self.__val = val
        self.__repo = repo

    def create(self, id, name, street, nr, city):
        """
          Create validate and store a student
          id,name, street,city- strings
          nr - int
          return Student
          raise ValueEror if the data is invalid, on duplicated id
        """
        # create Student instance
        st = Student(id, name, Address(street, nr, city))
        # validate, raise exception if student is invalid
        self.__val.validate(st)
        # store the student, raise exception if duplicated id
        self.__repo.store(st)
        return st

    def getNrStudents(self):
        """
          Return the number of students
          return int
        """
        return self.__repo.size()

    def remove(self, id):
        """
         Remove student with the given id
         id - string, student id
         return Student, the removed Student
         raise ValueError if there is no student with the given id
        """
        return self.__repo.remove(id)
    def search(self, criteria):
        """
          Search students with name containing criteria
          criteria string
          return list of students, where the name contains criteria
        """
        all = self.__repo.getAll()
        if criteria == "":
            return all

        rez = []
        for st in all:
            if criteria in st.getName():
                rez.append(st)
        return rez

    def update(self, id, name, street, nr, city):
        """
          Update student with the given id
          id,name, adr strings
          return the old student
          raise ValueError if the student is invalid, if there is no student with the given id
        """
        newSt = Student(id, name, Address(street, nr, city))

        # validate the student
        self.__val.validate(newSt)

        # get the old student
        oldSt = self.__repo.find(id)

        # update the student
        self.__repo.update(id, newSt)
        return oldSt
