package Repository;

import UI.Menu.ProgramState;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

//repo is a list of program states.
//first, write nothing to file with no append - clear the file -
//write all the structures with append at every logExec step
public class MyRepository implements IRepository {
    private List<ProgramState> repo;
    private PrintWriter logFile;

    public MyRepository(ProgramState state, String path) throws IOException {
        this.repo = new ArrayList<>();
        this.repo.add(state);

        this.logFile = new PrintWriter(new BufferedWriter(new FileWriter(path, true)));
        PrintWriter clearFile = new PrintWriter(new BufferedWriter(new FileWriter(path, false)));
        clearFile.write("");
        clearFile.close();
    }

    @Override
    public void add(ProgramState s) {
        this.repo.add(s);
    }

    @Override
    public List<ProgramState> getPrgList() {
        return this.repo;
    }

    @Override
    public void setPrgList(List<ProgramState> newList) {
        this.repo = newList;
    }

    @Override
    public void logProgramStateExec(ProgramState cur) throws IOException {
        logFile.write("Program State : " + Integer.toString(cur.getId()));
        logFile.println();
        logFile.println();
        logFile.write(cur.getExeStack().toString());
        logFile.println();
        logFile.println();
        logFile.write(cur.getSymTable().toString());
        logFile.println();
        logFile.println();
        logFile.write(cur.getOut().toString());
        logFile.println();
        logFile.println();
        logFile.write(cur.getFileTable().toString());
        logFile.println();
        logFile.println();
        logFile.write(cur.getHeap().toString());
        logFile.println();
        logFile.println();
        logFile.write("-------------------------");
        logFile.println();

    }

    @Override
    public void closeLogFile() {
        //Closing a previously closed stream has no effect
        this.logFile.close();
    }
}
