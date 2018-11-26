package Model;

//assigns to a variable(string) an expression that will be recursively evaluated
//until it returns an integer value and adds this pair variable-value in the Symbol Table
public class AssignmentStatement implements IStatement{
    private String id;
    private Expression exp;

    public AssignmentStatement(String id, Expression exp){
        this.id = id;
        this.exp = exp;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();

        try {
            int val = exp.eval(symTbl, heap);
            symTbl.put(id, val);
        }
        catch(MyException e){
            throw e;
        }
        return state;
    }
    public String toString(){
        return id + "=" + exp.toString();
    }
}
