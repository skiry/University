using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Data_Structures
{
    //list generic interface, wrapper
    //in use by Out Table
    public interface IList<T>
    {
        void add(T el);
        T get();
        int size();
        string ToString();
    }

}
