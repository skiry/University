package Model.Statements;

import Model.DataStructures.IDictionary;
import Model.DataStructures.IHeap;
import Model.DataStructures.IStack;
import Model.DataStructures.MyException;
import Model.Expressions.Expression;
import UI.Menu.ProgramState;

import java.io.IOException;

//writes exp's evaluation to the key from heap which is
// the value associated to the id from the Symbol Table given as parameter
//error if id not found
public class WriteHeapStatement implements IStatement {
    private String id;
    private Expression exp;

    public WriteHeapStatement(String id, Expression exp){
        this.id = id;
        this.exp = exp;
    }

    @Override
    public String toString() {
        return "wH(" + id + "," + exp.toString() + ")";
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();

        int addr = symTbl.get(id);
        int v = exp.eval(symTbl, heap);
        if(!heap.containsKey(addr)){
            throw new MyException("Invalid address exception!");
        }

        heap.put(addr, v);
        return null;
    }

}
