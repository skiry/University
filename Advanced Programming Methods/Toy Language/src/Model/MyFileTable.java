package Model;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.stream.Stream;

//FileTable implementation, also generic
//actually keeps <integer, pair<string,bufferedReader>> pairs
public class MyFileTable<K, V> implements IDictionary<K, V> {
    private HashMap<K, V> hm;

    public MyFileTable(){
        hm = new HashMap<>();

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
    public V get(K key) throws MyException {
        return hm.get(key);
    }

    public Set<K> keySet(){
        return hm.keySet();
    }

    public Collection values(){
        return hm.values();
    }

    @Override
    public String toString() {
        String res = "FileTable:";
        for(K el:hm.keySet()){
            res = res.concat(System.lineSeparator());
            res = res.concat(el.toString());
            res = res.concat(" --> ");
            if(hm.get(el) instanceof Pair) {
                res = res.concat((String) ((Pair) hm.get(el)).getFirst());
            }
        }
        return res;
    }

    @Override
    public void remove(K key){
        hm.remove(key);
    }

    public Stream<Map.Entry<K,V>> stream(){
        return this.hm.entrySet().stream();
    }
}
