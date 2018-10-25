package Model;

public interface IList<T> {
    void add(T el);
    T get() throws MyException;
    int size();
    String toString();
}
