package Model.Expressions;

import Model.DataStructures.IDictionary;
import Model.DataStructures.IHeap;
import Model.DataStructures.MyException;

public abstract class Expression {
    public abstract int eval(IDictionary<String, Integer> dict, IHeap<Integer, Integer> heap) throws MyException;
    public abstract String toString();
}
