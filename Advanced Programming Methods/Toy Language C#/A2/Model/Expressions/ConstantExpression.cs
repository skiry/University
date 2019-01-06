using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Expressions
{
    //simply a constant expression that stops the recursivity from other expressions and has just a number
    public class ConstantExpression : Expression{
        private int number;

        public ConstantExpression(int number)
        {
            this.number = number;
        }
        public override int eval(Data_Structures.IDictionary<string, int> dict)
        {
            return number;
        }
        public override string ToString()
        {
            return number.ToString();
        }
    }
}
