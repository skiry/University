package Model;

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
        try {
            int val = exp.eval(symTbl);
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
