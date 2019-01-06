using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Expressions
{
    public abstract class Expression
    {
        public abstract int eval(Model.Data_Structures.IDictionary<string, int> dict);
        public abstract override string ToString();
    }

}
