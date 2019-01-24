package Model.Expressions;

import Model.DataStructures.IDictionary;
import Model.DataStructures.IHeap;

//simply a constant expression that stops the recursivity from other expressions and has just a number
public class ConstantExpression extends Expression {
    private int number;

    public ConstantExpression(int number){
        this.number = number;
    }

    @Override
    public int eval(IDictionary<String, Integer> dict, IHeap<Integer, Integer> heap) {
        return number;
    }

    @Override
    public String toString() {
        return Integer.toString(number);
    }
}
