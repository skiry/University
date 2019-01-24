package Model.Statements;

import Model.DataStructures.*;
import Model.Expressions.Expression;
import UI.Menu.ProgramState;

import java.util.ArrayList;

//has 2 parameters: variable and an expression.
//maps the var to its corresponding id
public class newBarrierStatement implements IStatement {
    private Expression exp;
    private String var;

    public newBarrierStatement(String var, Expression exp){
        this.exp = exp;
        this.var = var;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();
        BarrierTable<Integer, Pair<Integer, ArrayList<Integer>>> barrierTable = (BarrierTable<Integer, Pair<Integer, ArrayList<Integer>>>) state.getBarrierTable();
        int value;

        synchronized (barrierTable){
            barrierTable.put(value = barrierTable.getUniqueId(), new Pair<>(exp.eval(symTbl, heap), new ArrayList<>()));
        }
        symTbl.put(var, value);
        return null;
    }


    public String toString(){
        return "newBarrier(" + var
                + ", " + exp.toString()
                + ")";
    }
}
