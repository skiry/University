package Repository;

import Model.MyException;
import Model.ProgramState;

import java.io.IOException;

public interface IRepository {
    void add(ProgramState s) throws MyException;
    ProgramState getCurrentProgram();
    void logProgramStateExec() throws IOException;
    void closeLogFile();
}
