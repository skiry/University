package sample;

public class TableViewElement <T, V>{
    private T key;
    private V value;

    TableViewElement (T key, V value){
        this.key = key;
        this.value = value;
    }

    public T getKey(){
        return key;
    }

    public V getValue(){
        return value;
    }
}
