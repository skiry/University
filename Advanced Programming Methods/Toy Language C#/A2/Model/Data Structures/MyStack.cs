using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Data_Structures
{
    //Execution Stack
    public class MyStack<T> : IStack<T> {
        private Stack<T> stack;
        private int nr;

        public MyStack()
        {
            stack = new Stack<T>();
        }

        public void push(T el)
        {
            stack.Push(el);
            ++nr;
        }
        
        public T pop()
        {
            if(isEmpty())
                throw new MyException("Empty stack");
            --nr;
            return stack.Pop();
        }
        public int length()
        {
            return nr;
        }
    
        public Boolean isEmpty()
        {
            return stack.Count() == 0;
        }

        public override string ToString()
        {
            String res = "ExeStack:";
            List<T> list = new List<T>(stack);
            //list.Reverse();
            foreach (Object el in list)
            {
                res += Environment.NewLine;
                res += String.Concat(el.ToString());
            }

            return res;
        }
    }

}
