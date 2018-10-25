package Repository;

import Model.MyException;
import Model.PrintStatement;
import Model.ProgramState;

import java.util.ArrayList;

public class MyRepository implements IRepository {
    private ProgramState[] repo;
    private int counter;
    public MyRepository(ProgramState state){
        this.repo = new ProgramState[5];
        this.repo[counter++] = state;
    }

    @Override
    public void add(ProgramState s) throws MyException {
        if(counter < this.repo.length)
            this.repo[counter++] = s;
        else throw new MyException("No more empty space in repository!");
    }

    @Override
    public ProgramState getCurrentProgram() {
        return repo[counter-1];
    }
}
