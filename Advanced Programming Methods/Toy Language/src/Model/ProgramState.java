package Model;

public class ProgramState {
    private IStack<IStatement> exeStack;
    private IDictionary<String, Integer> symTable;
    private IList<Integer> out;
    private IStatement originalProgram;

    public ProgramState(IStack<IStatement> exeStack,
                      IDictionary<String, Integer> symTable,
                      IList<Integer> out){
                      //IStatement originalProgram){
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        //this.originalProgram = deepcopy(originalProgram);
        //this.exeStack.push(originalProgram);
    }

    public IStack<IStatement> getExeStack() {
        return exeStack;
    }
    public IDictionary<String, Integer> getSymTable(){
        return symTable;
    }
    public IList<Integer> getOut(){
        return out;
    }
    IStatement getOriginalProgram(){
        return originalProgram;
    }

    void setExeStack(IStack<IStatement> exeStack) {
        this.exeStack = exeStack;
    }
    void setSymTable(IDictionary<String, Integer> symTable){
        this.symTable = symTable;
    }
    void setOut(IList<Integer> out){
        this.out = out;
    }
    void setOriginalProgram(IStatement originalProgram){
        this.originalProgram = originalProgram;
    }

}
