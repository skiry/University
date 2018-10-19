package Controller;

import Model.IAutomobile;
import Repository.IRepo;

public class Ctrl {
    private IRepo repo;
    public Ctrl(IRepo repo) {
        this.repo = repo;
    }

    public IAutomobile[] filter(String colour){
        return repo.filter(colour);
    }

    public void add(IAutomobile e){
        repo.add(e);
    }
}
