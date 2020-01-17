from Repository.GenericFileRepository import GenericFileRepository

from Service.ComentariuService import ComentariuService
from Service.StireService import StireService

from UserInterface.Console import Console

stireRepository = GenericFileRepository("Stire.pkl")
comentariuRepository = GenericFileRepository("Comentariu.pkl")


stireService = StireService(stireRepository)
comentariuService = ComentariuService(comentariuRepository, stireRepository)

console = Console(stireService, comentariuService)

console.runConsole()