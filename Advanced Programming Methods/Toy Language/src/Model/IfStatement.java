package Model;

//has 3 parameters: an expression and 2 statemets
//if the result of expression if evaluated as <> 0, then the first statement is pushed onto the Execution Stack
//otherwise, the second statement is pushed onto the Execution Stack
public class IfStatement implements IStatement {
    private Expression exp;
    private IStatement thenStatement, elseStatement;

    public IfStatement(Expression exp, IStatement thenStatement, IStatement elseStatement){
        this.exp = exp;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();

        if (exp.eval(symTbl, heap) != 0)
            stk.push(thenStatement);
        else
            stk.push(elseStatement);

        return state;
    }
    public String toString(){
        return "IF(" + exp.toString()
                + ") THEN(" + thenStatement.toString()
                + ") ELSE(" + elseStatement.toString()
                + ")";
    }
}
