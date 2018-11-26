package Controller;

import Model.DataStructures.*;
import Model.Statements.IStatement;
import Repository.IRepository;
import UI.Menu.ProgramState;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Collection;
import java.util.Map;
import java.util.stream.Collectors;

//keeps a reference to the repository
//oneStep calls execute() for the head of the Execution Stack
//allSteps calls oneStep() until the Execution Stack is empty
public class Controller {
    private IRepository repo;

    public Controller(IRepository repo){
        this.repo = repo;
    }

   private IHeap<Integer, Integer> conservativeGarbageCollector(Collection symTable,
                                                                MyHeap<Integer, Integer> heap){
        java.util.Map<Integer, Integer> x = heap.stream().filter( e -> symTable.contains(e.getKey())).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
        return new MyHeap<>(x);
    }
    public ProgramState oneStep() throws MyException, IOException {
        ProgramState state = repo.getCurrentProgram();
        IStack<IStatement> stk = state.getExeStack();

        System.out.println(state.getExeStack());
        System.out.println(state.getSymTable());
        System.out.println(state.getOut());
        System.out.println(state.getFileTable());
        System.out.println(state.getHeap());

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
        IDictionary<Integer, Pair<String, BufferedReader>> fileTable = new MyFileTable<>();

        try {
            while (!stk.isEmpty()) {
                oneStep();
                prg.setHeap(conservativeGarbageCollector(prg.getSymTable().values(), (MyHeap<Integer, Integer>) prg.getHeap()));
                repo.logProgramStateExec();
            }
            repo.closeLogFile();
            System.out.println(prg.getExeStack());
            System.out.println(prg.getSymTable());
            System.out.println(prg.getOut());
            System.out.println(prg.getFileTable());
            System.out.println(prg.getHeap());
        }
        catch(MyException exc){
            System.out.println(exc.getMessage());
        } catch (IOException e) {
            e.printStackTrace();
        }
        finally {
            ((MyFileTable<Integer, Pair<String, BufferedReader>>) fileTable).stream()
                    .forEach(s-> {
                        try {
                            s.getValue().getSecond().close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    });
        }
    }
}
