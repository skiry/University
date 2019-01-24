package Model.Statements;

import Model.DataStructures.IDictionary;
import Model.DataStructures.IHeap;
import Model.DataStructures.IStack;
import Model.DataStructures.MyException;
import Model.Expressions.Expression;
import UI.Menu.ProgramState;

import java.util.Stack;

//return statement. only restore the last symbol table
public class ReturnStatement implements IStatement {
    public ReturnStatement(){
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Stack<IDictionary<String, Integer>> symTbl = state.getAllSym();
        symTbl.pop();
        return null;
    }

    public String toString(){
        return "return;";
    }
}
