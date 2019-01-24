package Model.Statements;

import Model.DataStructures.IDictionary;
import Model.DataStructures.IHeap;
import Model.DataStructures.IStack;
import Model.DataStructures.MyException;
import Model.Expressions.Expression;
import Model.Expressions.VariableExpression;
import UI.Menu.ProgramState;

// has 4 parameters: first, the variable to which is to be assigned the value
// three expressions that are turned into an if-else pushed again onto the stack
// a=b?c:d -> if(b) {a=c} else {a=d}
public class ConditionalStatement implements IStatement {
    private Expression expToEvaluate, ifExp, thenExp;
    private String variable;

    public ConditionalStatement(String variable, Expression expToEvaluate, Expression ifExp, Expression thenExp){
        this.variable = variable;
        this.expToEvaluate = expToEvaluate;
        this.ifExp = ifExp;
        this.thenExp = thenExp;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();

        stk.push(new IfStatement(expToEvaluate,new AssignmentStatement(variable, ifExp),new AssignmentStatement(variable, thenExp)));

        return null;
    }


    public String toString(){
        return variable
                + " = " + expToEvaluate.toString()
                + " ? " + ifExp.toString()
                + " : " + thenExp.toString();
    }
}