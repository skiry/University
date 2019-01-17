package Model.Statements;

import Model.Expressions.Expression;
import Model.DataStructures.IDictionary;
import Model.DataStructures.IHeap;
import Model.DataStructures.MyException;
import UI.Menu.ProgramState;

//allocates memory in the heap for the variable varName
//in the symTable varName will have an unique address and in the heap
//that address will point to the evaluation of expression
public class NewStatement implements IStatement {
    private String varName;
    private Expression exp;

    public NewStatement(String varName, Expression exp){
        this.varName = varName;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();

        int result = exp.eval(symTbl, heap);
        int address = 1;

        for(int i = 1; i < heap.getHeapSize(); ++i){
            if(!heap.keySet().contains(i)){
                address = i;
                break;
            }
        }
        heap.put(address, result);
        symTbl.put(varName, address);

        return null;
    }

    @Override
    public String toString() {
        return "new(" + varName + "," + exp.toString() + ")";
    }
}
