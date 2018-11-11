package Model;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

//open the file fileName - if fileName already opened, throw exception -
//otherwise, add <unique FD,pair<fileName, bufferedReadder>> pair to fileTable to keep evidence of opened files
//also, to acces this file, add <varFileId, unique FD> pair to symbolTable
public class openRFileStatement implements IStatement {
    private String varFileId;
    private String fileName;
    private static int fileDescriptor = 1;

    public openRFileStatement(String varFileId, String fileName) {
        this.varFileId = varFileId;
        this.fileName = fileName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, FileNotFoundException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<Integer, Pair<String, BufferedReader>> fileTable = state.getFileTable();
        IDictionary<String, Integer> symTbl = state.getSymTable();

        BufferedReader myFile = null;

        for (Object el : fileTable.values()) {
            if (el instanceof Pair) {
                if (((Pair) el).getFirst() == fileName) {
                    throw new MyException("File Name already in the File Table");
                }
            }
        }

            myFile = new BufferedReader(new FileReader(fileName));
            fileTable.put(fileDescriptor, new Pair<>(fileName, myFile));
            symTbl.put(varFileId, fileDescriptor++);

            return state;
        }

    public String toString() {
        String res = "openRFile(";
        res = res.concat(varFileId);
        res = res.concat(",");
        res = res.concat(fileName);
        res = res.concat(")");
        return res;
    }
}