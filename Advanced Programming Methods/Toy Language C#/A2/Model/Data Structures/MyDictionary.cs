using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Data_Structures
{
    //Symbol Table
    //hashmap that keeps variable-value pairs
    public class MyDictionary<K, V> : IDictionary<K,V>  {
        private Dictionary<K, V> hm;

        public MyDictionary()
        {
            this.hm = new Dictionary<K, V>();
        }
        public V put(K key, V value)
        {
            if (hm.ContainsKey(key))
            {
                hm.Remove(key);
            }
            hm.Add(key, value);
            return value;
        }
        
        public int size()
        {
            return hm.Count();
        }
        
        public Boolean containsKey(K key)
        {
            return hm.ContainsKey(key);
        }
        
        public Boolean containsValue(V value)
        {
            return hm.ContainsValue(value);
        }
        
        public V get(K key)
        {
            if(!hm.ContainsKey(key))
                throw new MyException("No key");
            V result;
            hm.TryGetValue(key, out result);
            return result;
        }

        public override string ToString()
        {
            String res = "SymTable:";
            foreach (K el in keySet())
            {
                res += Environment.NewLine;
                res += el.ToString();
                res += " --> ";
                res += get(el).ToString();
            }
            return res;
        }
    
            public HashSet<K> keySet()
        {
            return new HashSet<K>(hm.Keys);
        }
    
            public HashSet<V> values()
        {
            return new HashSet<V>(hm.Values);
        }
    
            public void remove(K key)
        {
            hm.Remove(key);
        }
    }

}
