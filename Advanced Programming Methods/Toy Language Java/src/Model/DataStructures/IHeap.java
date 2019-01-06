package Model.DataStructures;

import java.util.Collection;
import java.util.Set;

//dictionary generic interface, wrapper
//in use by the Heap
public interface IHeap<K, V> {
    V put(K key, V value);
    int size();
    boolean containsKey(K key);
    boolean containsValue(V value);
    V get(K key) throws MyException;
    String toString();
    Set<K> keySet();
    Collection values();
    void remove(K key);
    int getHeapSize();
}
