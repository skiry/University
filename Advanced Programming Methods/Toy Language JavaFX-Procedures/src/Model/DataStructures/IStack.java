package Model.DataStructures;

import java.util.ArrayList;

//stack generic interface, wrapper
//in use by the Execution Stack
public interface IStack<T> {
    void push(T el);
    T pop() throws MyException;
    int length();
    boolean isEmpty();
    String toString();
    ArrayList<T> get();
}
