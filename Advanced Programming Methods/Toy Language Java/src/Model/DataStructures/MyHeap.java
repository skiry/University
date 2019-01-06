package Model.DataStructures;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.stream.Stream;

//Heap generic implementation
//actually keeps <integer, integer> pairs
public class MyHeap<K, V> implements IHeap<K, V> {
    Map<K, V> hm;
    private int nextAddress = 1;
    private int HEAPSIZE = 2048;

    public MyHeap(){
        hm = new HashMap<>();
    }

    public MyHeap(java.util.Map<K, V> nhm){
        hm = nhm;
    }

    @Override
    public V put(K key, V value) {
        return hm.put(key, value);
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

    public String toString(){
        String res = "Heap:";
        for(K el:hm.keySet()){
            res = res.concat(System.lineSeparator());
            res = res.concat(el.toString());
            res = res.concat(" --> ");
            res = res.concat(hm.get(el).toString());
        }
        return res;
    }

    public int getHeapSize(){
        return HEAPSIZE;
    }

    public Stream<Entry<K, V>> stream(){
        return hm.entrySet().stream();
    }
}
