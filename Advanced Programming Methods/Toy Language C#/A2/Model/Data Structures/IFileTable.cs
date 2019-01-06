using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;

namespace A2.Model.Data_Structures
{

    //dictionary generic interface, wrapper
    //in use by File Table
    public interface IFileTable<K, VKeyValuePair>
    {
        KeyValuePair<string, StreamReader> put(K key, KeyValuePair<string, StreamReader> value);
        int size();
        Boolean containsKey(K key);
        Boolean containsValue(KeyValuePair<string, StreamReader> value);
        KeyValuePair<string, StreamReader> get(K key);
        string ToString();
        HashSet<K> keySet();
        HashSet<KeyValuePair<string, StreamReader>> values();
        void remove(K key);
    }


}
