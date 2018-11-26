package Repository;

import Model.DataStructures.MyException;
import UI.Menu.ProgramState;

import java.io.IOException;

public interface IRepository {
    void add(ProgramState s) throws MyException;
    ProgramState getCurrentProgram();
    void logProgramStateExec() throws IOException;
    void closeLogFile();
}
