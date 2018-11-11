package Model;

//compund has 2 statements which are pushed onto the Execution Stack
public class CompoundStatement implements IStatement {
    private IStatement first, second;

    public CompoundStatement(IStatement first, IStatement second) {
        this.first = first;
        this.second = second;
    }
    @Override
    public ProgramState execute(ProgramState state) {
        IStack<IStatement> stk = state.getExeStack();
        stk.push(second);
        stk.push(first);
        return state;
    }
    public String toString(){
        return "(" + first.toString() + ";" + second.toString() + ")";
    }
}
