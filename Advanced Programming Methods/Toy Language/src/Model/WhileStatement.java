package Model;

public class WhileStatement implements IStatement {
    private Expression exp;
    private IStatement stmt;

    public WhileStatement(Expression exp, IStatement stmt){
        this.exp = exp;
        this.stmt = stmt;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();

        if(exp.eval(symTbl, heap) != 0){
            stk.push(this);
            stk.push(stmt);
        }
        return state;
    }

    @Override
    public String toString() {
        return "while(" + exp.toString() + ") " + stmt.toString();
    }
}
