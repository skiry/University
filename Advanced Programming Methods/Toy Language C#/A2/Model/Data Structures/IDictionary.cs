using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace A2.Model.Data_Structures
{

    //dictionary generic interface, wrapper
    //in use by Symbol Table
    public interface IDictionary<K, V>
    {
        V put(K key, V value);
        int size();
        Boolean containsKey(K key);
        Boolean containsValue(V value);
        V get(K key);
        string ToString();
        HashSet<K> keySet();
        HashSet<V> values();
        void remove(K key);
    }


}
