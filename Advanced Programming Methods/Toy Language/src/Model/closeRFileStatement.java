package Model;

import java.io.BufferedReader;
import java.io.IOException;

//search for the expression's result in the File Table
//if not found or expression not evaluated, throw error
//otherwise, close the file from the associated bufferedReader and remove the entry from the File Table
public class closeRFileStatement implements IStatement{
    private Expression expFileId;

    public closeRFileStatement(Expression expFileId){
        this.expFileId = expFileId;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException, IOException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<Integer, Pair<String, BufferedReader>> fileTable = state.getFileTable();
        IDictionary<String, Integer> symTbl = state.getSymTable();

        int result;
        try{
            result = expFileId.eval(symTbl);
        }
        catch(Exception e){
            throw new MyException("Error evaluating the expression");
        }
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
        else{
            myFile.close();
            fileTable.remove(result);
        }
        return state;
    }

    public String toString() {
        String res = "closeRFile(";
        res = res.concat(expFileId.toString());
        res = res.concat(")");
        return res;
    }
}
