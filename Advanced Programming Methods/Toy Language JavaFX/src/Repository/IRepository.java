package Repository;

import Model.DataStructures.MyException;
import UI.Menu.ProgramState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    void add(ProgramState s) throws MyException;
    List<ProgramState> getPrgList();
    void setPrgList(List<ProgramState> newList);
    void logProgramStateExec(ProgramState cur) throws IOException;
    void closeLogFile();
}
