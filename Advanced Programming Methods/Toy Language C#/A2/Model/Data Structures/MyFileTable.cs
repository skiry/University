using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Model.Data_Structures
{
    //FileTable implementation, also generic
    //actually keeps <integer, pair<string,bufferedReader>> pairs
    public class MyFileTable<K, KeyValuePair> : IFileTable<K, KeyValuePair> {
        private Dictionary<K, KeyValuePair<string, StreamReader>> hm;

        public MyFileTable()
        {
            hm = new Dictionary<K, KeyValuePair<string, StreamReader>>();
        }
        public KeyValuePair<string, StreamReader> put(K key, KeyValuePair<string, StreamReader> value)
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
        public Boolean containsValue(KeyValuePair<string, StreamReader> value)
        {
            return hm.ContainsValue(value);
        }
        public KeyValuePair<string, StreamReader> get(K key)
        {
            KeyValuePair<string, StreamReader> value;
            hm.TryGetValue(key, out value);
            return value;
        }

        public HashSet<K> keySet()
        {
            return new HashSet<K>(hm.Keys);
        }

        public HashSet<KeyValuePair<string, StreamReader>> values()
        {
            return new HashSet<KeyValuePair<string, StreamReader>>(hm.Values);
        }
        public override string ToString()
        {
            String res = "FileTable:";
            foreach (K el in keySet())
            {
                res += Environment.NewLine;
                res += el.ToString();
                res += " --> ";

                KeyValuePair<string, StreamReader> value;
                hm.TryGetValue(el, out value);
                res += value.Key;
            }
            return res;
        }
        public void remove(K key)
        {
            hm.Remove(key);
        }
    }
}
