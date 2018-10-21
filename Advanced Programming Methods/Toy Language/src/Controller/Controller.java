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
            IList<Integer> outList = repo.getCurrentProgram().getOut();
            for(int i = 0; i < outList.size(); ++i) {
                System.out.println(outList.get(i));
            }
        }
        catch(MyException exc){
            System.out.println(exc.getMessage());
        }
    }
}
