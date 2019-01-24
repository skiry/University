package Model.Statements;

import Model.DataStructures.*;
import Model.Expressions.BooleanExpression;
import Model.Expressions.Expression;
import UI.Menu.ProgramState;

//normal switch with 2 base cases and a default one
public class SwitchStatement implements IStatement{
    private Expression swExp, case1Exp, case2Exp;
    private IStatement case1St, case2St, defSt;

    public SwitchStatement(Expression swExp, Expression case1Exp, Expression case2Exp,
                           IStatement case1St, IStatement case2St, IStatement defSt){
        this.swExp = swExp;
        this.case1Exp = case1Exp;
        this.case2Exp = case2Exp;
        this.case1St = case1St;
        this.case2St = case2St;
        this.defSt = defSt;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stk = state.getExeStack();
        IDictionary<String, Integer> symTbl = state.getSymTable();
        IHeap<Integer, Integer> heap = state.getHeap();

        stk.push(new IfStatement(new BooleanExpression(BooleanSign.EQ, swExp, case1Exp), case1St, new IfStatement(new BooleanExpression(BooleanSign.EQ, swExp, case2Exp), case2St, defSt)));

        return null;
    }


    public String toString(){
        return "Switch(" + swExp.toString()
                + ")( case " + case1Exp.toString() + ":" + case1St.toString()
                + ")( case " + case2Exp.toString() + ":" + case2St.toString()
                + ")( default:" + defSt.toString();
    }
}