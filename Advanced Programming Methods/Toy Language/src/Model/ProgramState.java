package Model;

import java.io.BufferedReader;

//Program State keeps a reference to all important structures together with their getters and setters
public class ProgramState {
    private IStack<IStatement> exeStack;
    private IDictionary<String, Integer> symTable;
    private IList<Integer> out;
    private IStatement originalProgram;
    private IDictionary<Integer, Pair<String, BufferedReader>> fileTable;

    public ProgramState(IStack<IStatement> exeStack,
                      IDictionary<String, Integer> symTable,
                      IList<Integer> out,
                      IStatement originalProgram,
                        IDictionary<Integer, Pair<String, BufferedReader>> fileTable){
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.exeStack.push(originalProgram);
        this.fileTable = fileTable;
    }

    public IStack<IStatement> getExeStack() {

        return exeStack;
    }
    public IDictionary<String, Integer> getSymTable()
    {
        return symTable;
    }
    public IList<Integer> getOut(){

        return out;
    }
    IStatement getOriginalProgram(){

        return originalProgram;
    }
    public IDictionary<Integer, Pair<String, BufferedReader>> getFileTable() { return fileTable; };

    void setExeStack(IStack<IStatement> exeStack) {
        this.exeStack = exeStack;
    }
    void setSymTable(IDictionary<String, Integer> symTable)
    {
        this.symTable = symTable;
    }
    void setOut(IList<Integer> out){

        this.out = out;
    }
    void setOriginalProgram(IStatement originalProgram){

        this.originalProgram = originalProgram;
    }
    void setFileTable(IDictionary<Integer, Pair<String, BufferedReader>> fileTable){
        this.fileTable = fileTable;
    }

}
