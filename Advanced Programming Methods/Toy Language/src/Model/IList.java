package Model;

public interface IList<T> {
    void add(T el);
    T get(int index) throws MyException;
    int size();
}
