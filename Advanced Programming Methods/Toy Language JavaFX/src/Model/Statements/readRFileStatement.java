package Model.Statements;

import Model.DataStructures.*;
import Model.Expressions.Expression;
import UI.Menu.ProgramState;

import java.io.BufferedReader;
import java.io.IOException;

//evaluate the expression to search for that value in the fileTable
//if not found, throw error
//otherwise, S = read a line from the associated bufferedReader
//if read, add <varName, S> pair in the Symbol Table
public class readRFileStatement implements IStatement{
    private Expression expFileId;
    private String varName;

    public readRFileStatement(Expression expFileId, String varName){
        this.expFileId = expFileId;
        this.varName = varName;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<Integer, Pair<String, BufferedReader>> fileTable = state.getFileTable();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();

        int result = expFileId.eval(symTbl, heap);
        boolean exists = false;
        BufferedReader myFile = null;

        for(Integer el:fileTable.keySet()){
            if(el == result) {
                exists = true;
                myFile = fileTable.get(el).getSecond();
            }
        }
        if( !exists ){
            throw new MyException("Key not in File Table!");
        }
        String read = myFile.readLine();
        if(read != null) {
            symTbl.put(varName, Integer.parseInt(read));
        }
        else {
            symTbl.put(varName, 0);
        }
        return null;
    }


    public String toString() {
        String res = "readRFile(";
        res = res.concat(expFileId.toString());
        res = res.concat(",");
        res = res.concat(varName);
        res = res.concat(")");
        return res;
    }
}
