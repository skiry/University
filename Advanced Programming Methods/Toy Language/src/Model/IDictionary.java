package Model;

public interface IDictionary<K,V> {
    V put(K key, V value);
    int size();
    boolean containsKey(K key);
    boolean containsValue(V value);
    V get(K key) throws MyException;
    String toString();
}
