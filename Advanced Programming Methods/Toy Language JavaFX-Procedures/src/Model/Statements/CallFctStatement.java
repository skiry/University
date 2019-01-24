package Model.Statements;

import Model.DataStructures.*;
import Model.Expressions.Expression;
import UI.Menu.ProgramState;
import com.sun.xml.internal.bind.v2.model.core.ID;

import java.util.ArrayList;

//has 2 parameters: String - the procedure name
//                  ArrayList<Expression> - the formal parameters
public class CallFctStatement implements IStatement {
    private String procedureName;
    private ArrayList<Expression> exp;

    public CallFctStatement(String procedureName, ArrayList<Expression> exp){
        this.procedureName = procedureName;
        this.exp = exp;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IDictionary<String, Integer> newSymTable = new MyDictionary<>();
        IHeap<Integer, Integer> heap = state.getHeap();
        IProcTable<String, Pair<ArrayList<String>,IStatement>> procTable = state.getProcTable();
        ArrayList<Integer> values = new ArrayList<>();

        if(!procTable.containsKey(procedureName)){
            throw new MyException("Inexistent procedure!");
        }
        for(Expression ex:exp){
            values.add(ex.eval(symTbl, heap));
        }
        int i = 0;
        for(String el:procTable.get(procedureName).getFirst()){
            newSymTable.put(el, values.get(i++));
        }
        state.addToSymStack(newSymTable);
        stk.push(new ReturnStatement());
        stk.push(procTable.get(procedureName).getSecond());

        return null;
    }


    public String toString(){
        StringBuilder res = new StringBuilder();
        boolean isFirst = true;
        for(Expression ex : exp){
            if(isFirst){
                isFirst = false;
            }
            else{
                res.append(",");
            }
            res.append(ex.toString());
        }
        return "call" + procedureName + "(" + res + ")";
    }
}
