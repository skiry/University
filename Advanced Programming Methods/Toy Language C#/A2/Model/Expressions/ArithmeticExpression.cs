using System;
using A2.Model.Data_Structures;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Expressions
{
    //arithmetic expression receives 2 operands and 1 operator and evaluates recursively each operand
    //until it gets an integer
    //throws error if user wants to divide by 0
    public class ArithmeticExpression : Expression{
        private Expression e1, e2;
        private char operation;

        public ArithmeticExpression(char operation, Expression e1, Expression e2)
        {
            this.e1 = e1;
            this.e2 = e2;
            this.operation = operation;
        }
        public override int eval(Data_Structures.IDictionary<string, int> dict)
        {
            if( operation == '+' ){
                return e1.eval(dict) + e2.eval(dict);
            }
            else if( operation == '-' ){
                return e1.eval(dict) - e2.eval(dict);
            }
            else if( operation == '*' ){
                return e1.eval(dict) * e2.eval(dict);
            }
            int nr = e2.eval(dict);
            if(nr == 0)
                throw new MyException("Division by zero!");
            else if (nr != 0){
                return e1.eval(dict) / nr;
            }
            else Console.WriteLine("Only the basic arithmetic operations are permitted!");
            return 0;
        }
            public override string ToString()
        {
            return e1.ToString() + operation + e2.ToString();
        }
    }

}
