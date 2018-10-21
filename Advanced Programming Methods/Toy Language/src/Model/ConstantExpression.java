package Model;

public class ConstantExpression extends Expression {
    private int number;

    public ConstantExpression(int number){
        this.number = number;
    }

    @Override
    int eval(IDictionary<String, Integer> dict) {
        return number;
    }

    @Override
    public String toString() {
        return Integer.toString(number);
    }
}
