package Repository;

import Model.ProgramState;

import java.util.ArrayList;

public class MyRepository implements IRepository {
    private ProgramState repo;
    public MyRepository(ProgramState state){
        repo = state;
    }

    @Override
    public ProgramState getCurrentProgram() {
        return repo;
    }
}
