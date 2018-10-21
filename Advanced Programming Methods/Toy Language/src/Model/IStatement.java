package Model;

public interface IStatement {
    String toString();
    ProgramState execute(ProgramState state) throws MyException;
}
