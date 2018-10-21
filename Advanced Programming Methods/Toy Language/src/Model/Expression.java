package Model;

public abstract class Expression {
    abstract int eval(IDictionary<String, Integer> dict) throws MyException;
    public abstract String toString();
}
