package Controller;

import Model.DataStructures.*;
import Repository.IRepository;
import UI.Menu.ProgramState;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;
import java.util.stream.Collectors;



//////////////////////////////////////////pay attention to what every function expects / returns!




//keeps a reference to the repository
//oneStep calls execute() for the head of the Execution Stack
//allSteps calls oneStep() until the Execution Stack is empty
public class Controller {
    private ExecutorService executor;
    private IRepository repo;
    private boolean forbidden = false;
    public Controller(IRepository repo){
        this.repo = repo;
    }

    public List<ProgramState> getPrgList(){
        return repo.getPrgList();
    }

    private IHeap<Integer, Integer> conservativeGarbageCollector(Collection symTable,
                                                                        MyHeap<Integer, Integer> heap){
        java.util.Map<Integer, Integer> x = heap.stream().filter( e -> symTable.contains(e.getKey())).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
        return new MyHeap<>(x);
    }

    public static List<ProgramState> removeCompletedPrg(List<ProgramState> allPrg){
        return allPrg.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    private void oneStepForAllPrg(List<ProgramState> allPrg) throws Exception {
        AtomicReference<Exception> exc = null;
        AtomicBoolean thrown = new AtomicBoolean(false);
        allPrg.forEach(onePrg -> {
            try {
                repo.logProgramStateExec(onePrg);
            } catch (IOException e) {
                //e.printStackTrace();
            }
        });

        List<Callable<ProgramState>> callList = allPrg.stream()
                .map((ProgramState p) -> (Callable<ProgramState>) (p::oneStep))
                .collect(Collectors.toList());
        List<ProgramState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        thrown.set(true);
                        exc.set(e);
                    }
                    return allPrg.get(0);//will never reach this. just return the main prg state
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());

        allPrg.addAll(newPrgList);

        repo.setPrgList(allPrg);
        if(thrown.get()) {
            throw exc.get();
        }
    }

    private void lastPrint(ProgramState prgState) throws IOException {
        //print all the data after the last execution step from the stack
        System.out.println(prgState.getId());
        System.out.println(prgState.getExeStack());
        System.out.println(prgState.getSymTable());
        System.out.println(prgState.getOut());
        System.out.println(prgState.getFileTable());
        System.out.println(prgState.getHeap());
        repo.logProgramStateExec(prgState);
    }

    public List<ProgramState> beforeAllStep(){
        executor = Executors.newFixedThreadPool(2);
        return removeCompletedPrg(repo.getPrgList());
    }

    public void allStep(List<ProgramState> prgList) throws Exception {
        if(prgList.size() > 0) {
            //prgList.get(0), the first statement, they all have the same heap
            Set<Integer> allSyms = new HashSet<>();
            prgList.forEach(prg -> prg.getSymTable()
                    .keySet()
                    .forEach(el -> {
                        try {
                            allSyms.add(prg.getSymTable().get(el));
                        } catch (MyException e) {
                            e.printStackTrace();
                        }
                    }));
            IHeap<Integer, Integer> heap = prgList.get(0).getHeap();

            heap.setHeap((MyHeap<Integer, Integer>) conservativeGarbageCollector((Collection) allSyms, (MyHeap<Integer, Integer>) heap));
            //WRONG : AM STAT..MULT PE ASTA! PAY ATTENTION TO WHAT IS VALUE AND WHAT IS REFERENCE AND HOW IT ACTUALLY MODIFIES
            //i was actually editing A heap from A program state, not the entire heap that was kept as reference by that 'A' program state...sad story
            //prgList.get(0).setHeap()((MyHeap<Integer, Integer>) conservativeGarbageCollector((Collection) allSyms, (MyHeap<Integer, Integer>) prgList.get(0).setHeap()));
            try{
                oneStepForAllPrg(prgList);
            }
            catch(Exception e){
                throw e;
            }
            prgList.stream()
                    .filter(prg -> !prg.isNotCompleted())
                    .forEach(prgState -> {
                        try {
                            lastPrint(prgState);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    });
            removeCompletedPrg(repo.getPrgList());
        }
        else{
            if(!forbidden) {
                prgList = removeCompletedPrg(repo.getPrgList());
                afterAllStep(prgList);
            }
            System.out.println("Done with this program!");
            forbidden = true;
        }
    }

    private void afterAllStep(List<ProgramState> prgList){
        executor.shutdownNow();

        List<ProgramState> tmpList = repo.getPrgList();
        ((MyFileTable<Integer, Pair<String, BufferedReader>>) tmpList.get(0).getFileTable()).stream()
                .forEach(s-> {
                    try {
                        s.getValue().getSecond().close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                });
        repo.closeLogFile();
        repo.setPrgList(prgList);
    }
}
