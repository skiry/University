package Model;

//list generic interface, wrapper
//in use by Out Table
public interface IList<T> {
    void add(T el);
    T get() throws MyException;
    int size();
    String toString();
}
