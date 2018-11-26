package Model;

//Pair class for <String-BufferedReader> pair implementation
public class Pair<K, V> {
    private K key;
    private V value;

    Pair(K key, V value){
        this.key = key;
        this.value = value;
    }

    K getFirst(){
        return key;
    }

   public V getSecond(){
        return value;
    }
}
