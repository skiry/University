package Model;

import java.util.Collections;

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
        try {
            if (exp.eval(symTbl) != 0)
                stk.push(thenStatement);
            else
                stk.push(elseStatement);
        }
        catch(MyException e){
            throw e;
        }
        return state;
    }
    public String toString(){
        return "IF(" + exp.toString()
                + ") THEN(" + thenStatement.toString()
                + ") ELSE(" + elseStatement.toString()
                + ")";
    }
}
