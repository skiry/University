using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Data_Structures
{
    //stack generic interface, wrapper
    //in use by the Execution Stack
    public interface IStack<T>
    {
        void push(T el);
        T pop();
        int length();
        Boolean isEmpty();
        string ToString();
    }

}
