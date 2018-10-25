package Repository;

import Model.MyException;
import Model.ProgramState;

public interface IRepository {
    void add(ProgramState s) throws MyException;
    ProgramState getCurrentProgram();
}
