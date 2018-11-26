package Model;

public abstract class Expression {
    abstract int eval(IDictionary<String, Integer> dict, IHeap<Integer, Integer> heap) throws MyException;
    public abstract String toString();
}
