package Model;

//stack generic interface, wrapper
//in use by the Execution Stack
public interface IStack<T> {
    void push(T el);
    T pop() throws MyException;
    int length();
    boolean isEmpty();
    String toString();
}
