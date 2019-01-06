package Model.Statements;

import Model.DataStructures.MyException;
import UI.Menu.ProgramState;

import java.io.IOException;

public interface IStatement {
    String toString();
    ProgramState execute(ProgramState state) throws MyException, IOException;
}
