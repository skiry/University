package UI.Menu;

import Model.DataStructures.*;
import Model.Statements.IStatement;
import com.sun.xml.internal.bind.v2.model.core.ID;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Dictionary;
import java.util.Stack;

//Program State keeps a reference to all important structures together with their getters and setters
public class ProgramState {
    private IStack<IStatement> exeStack;
    private Stack<IDictionary<String, Integer>> symTable;
    private IList<Integer> out;
    private IStatement originalProgram;
    private IDictionary<Integer, Pair<String, BufferedReader>> fileTable;
    private IHeap<Integer, Integer> heap;
    private static ArrayList<Integer> uniqueIds = new ArrayList<>();
    private IDictionary<Integer, Pair<Integer,ArrayList<Integer>>> barrierTable;
    private IProcTable<String, Pair<ArrayList<String>, IStatement>> procTable;
    private int id;

    public ProgramState(IStack<IStatement> exeStack,
                        Stack<IDictionary<String, Integer>> symTable,
                        IList<Integer> out,
                        IStatement originalProgram,
                        IDictionary<Integer, Pair<String, BufferedReader>> fileTable,
                        IHeap<Integer, Integer> heap,
                        IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> barrierTable,
                        IProcTable<String, Pair<ArrayList<String>, IStatement>> procTable,
                        int id){
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.exeStack.push(originalProgram);
        this.fileTable = fileTable;
        this.heap = heap;
        this.barrierTable = barrierTable;
        this.procTable = procTable;
        this.id = id;
        uniqueIds.add(id);
    }

    public IStack<IStatement> getExeStack() {

        return exeStack;
    }
    public IDictionary<String, Integer> getSymTable()
    {
        return symTable.peek();
    }
    public Stack<IDictionary<String, Integer>> getAllSym() { return symTable; }
    public IList<Integer> getOut(){

        return out;
    }
    IStatement getOriginalProgram(){

        return originalProgram;
    }
    public IDictionary<Integer, Pair<String, BufferedReader>> getFileTable() { return fileTable; }

    public IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> getBarrierTable(){
        return barrierTable;
    }

    public IProcTable<String, Pair<ArrayList<String>, IStatement>> getProcTable() { return procTable; }
    public int getId(){
        return id;
    }

    public static Integer getUniqueId(){
        int value = uniqueIds.get(uniqueIds.size() - 1);
        uniqueIds.add(value + 1);
        return value + 1;
    }
    void setExeStack(IStack<IStatement> exeStack) {
        this.exeStack = exeStack;
    }
    void setSymTable(Stack<IDictionary<String, Integer>> symTable)
    {
        this.symTable = symTable;
    }
    void setOut(IList<Integer> out){

        this.out = out;
    }
    void setOriginalProgram(IStatement originalProgram){

        this.originalProgram = originalProgram;
    }
    void setFileTable(IDictionary<Integer, Pair<String, BufferedReader>> fileTable){
        this.fileTable = fileTable;
    }

    public IHeap<Integer, Integer> getHeap() {
        return heap;
    }

    public void setHeap(IHeap<Integer, Integer> heap) {
        this.heap = heap;
    }

    public void addToSymStack(IDictionary<String, Integer> sym){
        this.symTable.push(sym);
    }
    public boolean isNotCompleted(){
        return !exeStack.isEmpty();
    }

    public ProgramState oneStep() throws MyException, IOException {
        System.out.println(id);
        System.out.println(this.getExeStack());
        System.out.println(this.getSymTable());
        System.out.println(this.getOut());
        System.out.println(this.getFileTable());
        System.out.println(this.getHeap());

        System.out.println("----------------------------------------------------");
        System.out.println("OVERALL SUNT CU ID " + id + " SI AM HEAPUL ASTA ");
        System.out.println(this.getHeap().toString());
        System.out.println("----------------------------------------------------");
        if(exeStack.isEmpty()) {
            throw new MyException("Empty Execution Stack!!!");
        }
        IStatement current = exeStack.pop();
        System.out.println("\n"+current.toString()+"\n");

        return current.execute(this);
    }
}
