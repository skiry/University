package Model;

import java.util.Collections;
import java.util.List;

//adds to the Out Table the integer result from the exp's evaluation
public class PrintStatement implements IStatement {
    private Expression exp;

    public PrintStatement(Expression exp){
        this.exp = exp;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IList<Integer> out = state.getOut();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        out.add(exp.eval(symTbl));
        return state;
    }
    public String toString(){
        return "print(" + exp.toString() + ")";
    }
}
