package Model.DataStructures;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

//Symbol Table
//hashmap that keeps variable-value pairs
public class MyDictionary<K,V> implements IDictionary<K,V>  {
    private HashMap<K,V> hm;

    public MyDictionary(){
        this.hm = new HashMap<>();
    }
    @Override
    public V put(K key, V value) {
        hm.put(key,value);
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
    public V get(K key) throws MyException {
        if(!hm.containsKey(key))
            throw new MyException("No " + " key");
        return hm.get(key);
    }

    public String toString(){
        String res = "SymTable:";
        for(K el:hm.keySet()){
            res = res.concat(System.lineSeparator());
            res = res.concat(el.toString());
            res = res.concat(" --> ");
            res = res.concat(hm.get(el).toString());
        }
        return res;
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
