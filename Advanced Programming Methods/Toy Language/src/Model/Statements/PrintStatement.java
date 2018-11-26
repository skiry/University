package Model.Statements;

import Model.DataStructures.IDictionary;
import Model.DataStructures.IHeap;
import Model.DataStructures.IList;
import Model.DataStructures.MyException;
import Model.Expressions.Expression;
import UI.Menu.ProgramState;

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
        IHeap<Integer, Integer> heap = state.getHeap();

        out.add(exp.eval(symTbl, heap));
        return state;
    }
    public String toString(){
        return "print(" + exp.toString() + ")";
    }
}
