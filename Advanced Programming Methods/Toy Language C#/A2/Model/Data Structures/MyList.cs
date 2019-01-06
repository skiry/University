using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Data_Structures
{
    //Out Table implemented as an array deque because we needed the most recent output on the first positions
    public class MyList<T> : IList<T> {
        private Queue<T> list;

        public MyList()
        {
            list = new Queue<T>();
        }
    
        public void add(T el)
        {
            list.Enqueue(el);
        }
    
        public T get()
        {
            if(list.Count() == 0)
                throw new MyException("Empty Out Array!");
            return list.Peek();
        }
    
        public int size()
        {
            return list.Count();
        }
    
        public override String ToString()
        {
            String res = "Out:";
            foreach (T el in list)
            {
                res += Environment.NewLine;
                res += el.ToString();
            }
            return res;
        }
    }

}
