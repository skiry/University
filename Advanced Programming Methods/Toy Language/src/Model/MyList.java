package Model;

import java.util.ArrayDeque;
import java.util.Queue;

public class MyList<T> implements IList<T> {
    private Queue<T> list;

    public MyList(){
        this.list = new ArrayDeque<>();
    }

    @Override
    public void add(T el) {
        list.add(el);
    }

    @Override
    public T get()throws MyException {
        if(list.isEmpty())
            throw new MyException("Empty Out Array!");
        return this.list.peek();
    }

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public String toString(){
        String res = "Out={";
        res = res.concat(list.toString());
        res = res.concat("}");
        return res;
    }
}
