from ex28_gui.domain.validators import StudentValidator
from ex28_gui.repository.file import StudentFileRepository
from ex28_gui.repository.inmemory import StudentRepository
from ex28_gui.controllers.controllers import StudentController 
from ex28_gui.ui.console import ConsoleUI
from ex28_gui.ui.gui import StudentGUI

#Application coordinator
#Use dependency injection pattern to asemble the application

#create a validator
val = StudentValidator()

#create repository
#repo = StudentRepository()

repo = StudentFileRepository("students.txt")

#create controller and inject dependencies
ctr = StudentController(val, repo)

#create console ui and provide (inject) the controller
#ui = ConsoleUI(ctr)
ui = StudentGUI(ctr)
ui.startUI()

