package Model.Statements;

import Model.DataStructures.*;
import UI.Menu.ProgramState;

import java.util.Set;

public class ForkStatement implements IStatement{
    private IStatement forkedStmt;
    public ForkStatement(IStatement forkedStmt){
        this.forkedStmt = forkedStmt;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException{
        IStack<IStatement> forkedExeStack = new MyStack<>();
        IDictionary<String, Integer> forkedSymTable = new MyDictionary<>();
        Set<String> keys = state.getSymTable().keySet();
        for(String it : keys){
            forkedSymTable.put(it, state.getSymTable().get(it));
        }
        ProgramState forkedPrg = new ProgramState(forkedExeStack, forkedSymTable, state.getOut(), forkedStmt, state.getFileTable(), state.getHeap(), state.getId() * 10);
        forkedPrg.setHeap(state.getHeap());
        return forkedPrg;
    }
    @Override
    public String toString(){
        return "fork(" + forkedStmt.toString() + ")";
    }
}
