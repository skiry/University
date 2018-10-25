package Controller;

import Model.*;
import Repository.IRepository;

public class Controller {
    private IRepository repo;

    public Controller(IRepository repo){
        this.repo = repo;
    }

    public ProgramState oneStep(ProgramState state) throws MyException{
        IStack<IStatement> stk = state.getExeStack();
        System.out.println(state.getExeStack());
        System.out.println(state.getSymTable());
        System.out.println(state.getOut());
        if(stk.isEmpty()) {
            throw new MyException("Empty Execution Stack!!!");
        }
        IStatement current = stk.pop();
        System.out.println(current.toString());

        return current.execute(state);
    }
    public void allSteps(){
        ProgramState prg = repo.getCurrentProgram();
        IStack<IStatement> stk = prg.getExeStack();
        try {
            while (!stk.isEmpty()) {
                oneStep(prg);
            }
            System.out.println(prg.getExeStack());
            System.out.println(prg.getSymTable());
            System.out.println(prg.getOut());
        }
        catch(MyException exc){
            System.out.println(exc.getMessage());
        }
    }
}
