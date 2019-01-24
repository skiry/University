package sample;

public class TripleTableViewElement <T, V, Q>{
    private T key;
    private V value;
    private Q list;

    TripleTableViewElement (T key, V value, Q list){
        this.key = key;
        this.value = value;
        this.list = list;
    }

    public T getKey(){
        return key;
    }

    public V getValue(){
        return value;
    }

    public Q getList() { return list; }
}
