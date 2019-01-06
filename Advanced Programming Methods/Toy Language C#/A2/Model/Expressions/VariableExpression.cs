using System;
using System.Collections.Generic;
using A2.Model.Data_Structures;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Expressions
{
    //returns the value associated to id from the Symbol Table given as parameter
    //error if id not found
    public class VariableExpression : Expression{
        private string id;

        public VariableExpression(String id)
        {
            this.id = id;
        }
        public override int eval(Data_Structures.IDictionary<string, int> dict)
        {
            if(!dict.containsKey(id))
                throw new MyException("Variable not in symbol table!");
            return dict.get(id);
        }
            public override string ToString()
        {
            return id;
        }
    }
}
