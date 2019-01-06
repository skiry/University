using System;
using A2.UI;
using A2.Model.Data_Structures;
using A2.Model.Expressions;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Statements
{
    //assigns to a variable(string) an expression that will be recursively evaluated
    //until it returns an integer value and adds this pair variable-value in the Symbol Table
    public class AssignmentStatement : IStatement
    {
    private string id;
    private Expression exp;

    public AssignmentStatement(string id, Expression exp)
    {
        this.id = id;
        this.exp = exp;
    }
    public ProgramState execute(ProgramState state)
    {
        IStack<IStatement> stk = state.getExeStack();
        Data_Structures.IDictionary<string, int> symTbl = state.getSymTable();

        try {
            int val = exp.eval(symTbl);
            symTbl.put(id, val);
        }
        catch(MyException e){
            throw e;
        }
        return state;
    }
    public override string ToString()
    {
        return id + "=" + exp.ToString();
    }
}

}
