package Model;

import java.util.HashMap;

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
        String res = "symTable={";
        res = res.concat(hm.toString());
        res = res.concat("}");
        return res;
    }
}
