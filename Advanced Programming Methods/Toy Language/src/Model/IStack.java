package Model;

public interface IStack<T> {
    void push(T el);
    T pop() throws MyException;
    int length();
    boolean isEmpty();
}
