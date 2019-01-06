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
    //has 3 parameters: an expression and 2 statemets
    //if the result of expression if evaluated as <> 0, then the first statement is pushed onto the Execution Stack
    //otherwise, the second statement is pushed onto the Execution Stack
    public class IfStatement : IStatement{
        private Expression exp;
        private IStatement thenStatement, elseStatement;

        public IfStatement(Expression exp, IStatement thenStatement, IStatement elseStatement)
        {
            this.exp = exp;
            this.thenStatement = thenStatement;
            this.elseStatement = elseStatement;
        }
        public ProgramState execute(ProgramState state)
        {
            IStack<IStatement> stk = state.getExeStack();
            Data_Structures.IDictionary<string, int> symTbl = state.getSymTable();

            if (exp.eval(symTbl) != 0)
                stk.push(thenStatement);
            else
                stk.push(elseStatement);

            return state;
        }
        public override string ToString()
        {
            return "IF(" + exp.ToString()
                    + ") THEN(" + thenStatement.ToString()
                    + ") ELSE(" + elseStatement.ToString()
                    + ")";
        }
    }
}
