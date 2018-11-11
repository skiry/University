package Model;

import java.util.*;

//Execution Stack
public class MyStack<T> implements IStack<T> {
    private Stack<T> stack;
    private int nr;

    public MyStack(){
        this.stack = new Stack<>();
    }
    @Override
    public void push(T el) {
        stack.push(el);
        ++nr;
    }

    @Override
    public T pop() throws MyException{
        if(isEmpty())
            throw new MyException("Empty stack");
        --nr;
        return stack.pop();
    }

    @Override
    public int length() {
        return nr;
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    public String toString(){
        String res = "ExeStack:";
        Collections.reverse(stack);
        ArrayList<T> list = new ArrayList<>(stack);
        for(Object el:list){
            res = res.concat(System.lineSeparator());
            res = res.concat(el.toString());
        }
        Collections.reverse(stack);
        return res;
    }
}
