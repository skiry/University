package Model.DataStructures;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

//Procedure Table
//hashmap that keeps variable-value pairs
public class MyProcTable<K,V> implements IProcTable<K,V> {
    private HashMap<K,V> hm;

    public MyProcTable(){
        this.hm = new HashMap<>();
    }

    @Override
    public V put(K key, V value) {
        hm.put(key, value);
        return value;
    }

    @Override
    public int size() {
        return hm.size();
    }

    @Override
    public boolean containsKey(K key) {
        return hm.containsKey(key);
    }

    @Override
    public boolean containsValue(V value) {
        return hm.containsValue(value);
    }

    @Override
    public V get(K key) {
        return hm.get(key);
    }

    @Override
    public Set<K> keySet() {
        return hm.keySet();
    }

    @Override
    public Collection values() {
        return hm.values();
    }

    @Override
    public void remove(K key) {
        hm.remove(key);
    }
}
