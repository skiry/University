package Controller;

import Model.*;
import Repository.IRepository;

import java.io.IOException;

//keeps a reference to the repository
//oneStep calls execute() for the head of the Execution Stack
//allSteps calls oneStep() until the Execution Stack is empty
public class Controller {
    private IRepository repo;

    public Controller(IRepository repo){
        this.repo = repo;
    }

    public ProgramState oneStep() throws MyException, IOException {
        ProgramState state = repo.getCurrentProgram();
        IStack<IStatement> stk = state.getExeStack();

        System.out.println(state.getExeStack());
        System.out.println(state.getSymTable());
        System.out.println(state.getOut());

        if(stk.isEmpty()) {
            throw new MyException("Empty Execution Stack!!!");
        }
        IStatement current = stk.pop();
        System.out.println("\n"+current.toString()+"\n");

        return current.execute(state);
    }
    public void allSteps(){
        ProgramState prg = repo.getCurrentProgram();
        IStack<IStatement> stk = prg.getExeStack();
        try {
            while (!stk.isEmpty()) {
                oneStep();
                repo.logProgramStateExec();
            }
            repo.closeLogFile();
            System.out.println(prg.getExeStack());
            System.out.println(prg.getSymTable());
            System.out.println(prg.getOut());
        }
        catch(MyException exc){
            System.out.println(exc.getMessage());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
