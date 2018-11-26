package Model;

//arithmetic expression receives 2 operands and 1 operator and evaluates recursively each operand
//until it gets an integer
//throws error if user wants to divide by 0
public class ArithmeticExpression extends Expression {
    private Expression e1, e2;
    private char operation;

    public ArithmeticExpression(char operation, Expression e1, Expression e2){
        this.e1 = e1;
        this.e2 = e2;
        this.operation = operation;
    }

    @Override
    int eval(IDictionary<String, Integer> dict, IHeap<Integer, Integer> heap) throws MyException{
        if( operation == '+' ){
            return e1.eval(dict, heap) + e2.eval(dict, heap);
        }
        else if( operation == '-' ){
            return e1.eval(dict, heap) - e2.eval(dict, heap);
        }
        else if( operation == '*' ){
            return e1.eval(dict, heap) * e2.eval(dict, heap);
        }
        int nr = e2.eval(dict, heap);
        if(nr == 0)
            throw new MyException("Division by zero!");
        else if (nr != 0){
            return e1.eval(dict, heap) / nr;
        }
        else System.out.println("Only the basic arithmetic operations are permitted!");
        return 0;
    }

    @Override
    public String toString() {
        return e1.toString() + operation + e2.toString();
    }
}
