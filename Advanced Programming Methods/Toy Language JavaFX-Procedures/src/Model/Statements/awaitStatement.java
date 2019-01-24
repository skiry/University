package Model.Statements;

import Model.DataStructures.*;
import Model.Expressions.Expression;
import UI.Menu.ProgramState;

import java.util.ArrayList;

//has 1 parameter: variable.
//awaits for the corresponding id from the barrier table of the variable var.
public class awaitStatement implements IStatement {
    private String var;

    public awaitStatement(String var){
        this.var = var;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();
        IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> barrierTable = state.getBarrierTable();
        int foundIndex;

        synchronized (barrierTable) {
            if (!(symTbl.containsKey(var))) {
                throw new MyException("Variable not in Symbol Table!");
            } else {
                foundIndex = symTbl.get(var);
                if (!(barrierTable.containsKey(foundIndex))) {
                    throw new MyException("Variable not in Barrier Table!");
                } else {
                    Pair<Integer, ArrayList<Integer>> result = barrierTable.get(foundIndex);
                    if (result.getFirst() > result.getSecond().size()) {
                        if (result.getSecond().contains(state.getId())) {
                            stk.push(this);
                        } else {
                            result.getSecond().add(state.getId());
                            stk.push(this);
                        }
                    }
                }
            }
        }

        return null;
    }


    public String toString(){
        return "await(" + var + ")";
    }
}