package Model;

import java.util.ArrayList;

public class MyList<T> implements IList<T> {
    private ArrayList<T> list;

    public MyList(){
        this.list = new ArrayList<>();
    }

    @Override
    public void add(T el) {
        list.add(el);
    }

    @Override
    public T get(int index)throws MyException {
        if(index >= size())
            throw new MyException("Index out of range!");
        return list.get(index);
    }

    @Override
    public int size() {
        return list.size();
    }
}
