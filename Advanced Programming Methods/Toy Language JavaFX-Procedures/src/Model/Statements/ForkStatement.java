package Model.Statements;

import Model.DataStructures.*;
import UI.Menu.ProgramState;

import java.util.ArrayList;
import java.util.Random;
import java.util.Set;
import java.util.Stack;

public class ForkStatement implements IStatement{
    private IStatement forkedStmt;
    private ArrayList<Integer> uniqueIds;
    public ForkStatement(IStatement forkedStmt){
        this.forkedStmt = forkedStmt;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException{
        IStack<IStatement> forkedExeStack = new MyStack<>();
        Stack<IDictionary<String, Integer>> forkedSymTable = new Stack<>();
        ArrayList<IDictionary<String, Integer>> symTbl = new ArrayList<>(state.getAllSym());

        for(IDictionary<String, Integer> dict : symTbl) {
            Set<String> keys = dict.keySet();
            IDictionary<String, Integer> currentSymTable = new MyDictionary<>();
            for (String it : keys) {
                currentSymTable.put(it, state.getSymTable().get(it));
            }
            forkedSymTable.push(currentSymTable);
        }
        ProgramState forkedPrg = new ProgramState(forkedExeStack, forkedSymTable, state.getOut(), forkedStmt, state.getFileTable(), state.getHeap(), state.getBarrierTable(), state.getProcTable(), state.getUniqueId());
        forkedPrg.setHeap(state.getHeap());
        return forkedPrg;
    }

    @Override
    public String toString(){
        return "fork(" + forkedStmt.toString() + ")";
    }
}
