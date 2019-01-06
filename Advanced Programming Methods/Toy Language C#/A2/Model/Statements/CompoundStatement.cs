using System;
using A2.UI;
using A2.Model.Data_Structures;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Statements
{
    //compund has 2 statements which are pushed onto the Execution Stack
    public class CompoundStatement : IStatement{
        private IStatement first, second;

        public CompoundStatement(IStatement first, IStatement second)
        {
            this.first = first;
            this.second = second;
        }
        public ProgramState execute(ProgramState state)
        {
            IStack<IStatement> stk = state.getExeStack();
            stk.push(second);
            stk.push(first);
            return state;
        }
        public override string ToString()
        {
            return "(" + first.ToString() + ";" + second.ToString() + ")";
        }
    }
}
