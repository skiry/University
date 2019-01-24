package Model.Statements;

import Model.DataStructures.IStack;
import UI.Menu.ProgramState;

public class SleepStatement implements IStatement {
    private int number;

    public SleepStatement(int number){
        this.number = number;
    }
    @Override
    public ProgramState execute(ProgramState state) {
        IStack<IStatement> stk = state.getExeStack();
        if(number != 0){
            stk.push(new SleepStatement(number - 1));
        }
        return null;
    }

    public String toString(){
        return "sleep(" + number + ")";
    }
}
