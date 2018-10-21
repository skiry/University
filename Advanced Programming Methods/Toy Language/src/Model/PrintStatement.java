package Model;

import java.util.Collections;
import java.util.List;

public class PrintStatement implements IStatement {
    private Expression exp;

    public PrintStatement(Expression exp){
        this.exp = exp;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IList<Integer> out = state.getOut();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        try{
            out.add(exp.eval(symTbl));
        }
        catch(MyException e){
            throw e;
        }
        return state;
    }
    public String toString(){
        return "print(" + exp.toString() + ")";
    }
}
