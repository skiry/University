using System;
using A2.UI;
using A2.Model.Expressions;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Statements
{
    //adds to the Out Table the integer result from the exp's evaluation
    public class PrintStatement : IStatement{
        private Expression exp;

        public PrintStatement(Expression exp)
        {
            this.exp = exp;
        }
        public ProgramState execute(ProgramState state)
        {
            Data_Structures.IList<int> outList = state.getOut();
            Data_Structures.IDictionary<string, int> symTbl = state.getSymTable();

            outList.add(exp.eval(symTbl));
            return state;
        }
        public override string ToString()
        {
            return "print(" + exp.ToString() + ")";
        }
    }
}
