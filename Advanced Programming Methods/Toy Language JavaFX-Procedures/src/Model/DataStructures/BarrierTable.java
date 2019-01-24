package Model.DataStructures;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

public class BarrierTable<K,V> implements IDictionary<K,V> {
    private HashMap<K,V> hm;
    private ArrayList<Integer> uniqueIds;

    public BarrierTable(){
        hm = new HashMap<>();
        uniqueIds = new ArrayList<>();
    }

    @Override
    public V put(K key, V value) {
        if(!uniqueIds.contains(key)){
            uniqueIds.add((Integer)key);
        }
        return hm.put(key, value);
    }

    @Override
    public int size() {
        return hm.size();
    }

    public Integer getUniqueId(){
        if(uniqueIds.size() == 0) return 1;
        return uniqueIds.get(uniqueIds.size() - 1) + 1;
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
