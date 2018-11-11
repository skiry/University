package Model;

import java.io.FileNotFoundException;
import java.io.IOException;

public interface IStatement {
    String toString();
    ProgramState execute(ProgramState state) throws MyException, IOException;
}
