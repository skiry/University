package Model;

//boolean expression receives 2 operands and 1 operator and evaluates recursively each operand
//until it gets an integer. return 1 if relation is true, 0 otherwise
//throws error if user wants to divide by 0
public class BooleanExpression extends Expression {
    private BooleanSign operation;
    private Expression e1, e2;

    public BooleanExpression(BooleanSign operation, Expression e1, Expression e2){
        this.operation = operation;
        this.e1 = e1;
        this.e2 = e2;
    }

    @Override
    int eval(IDictionary<String, Integer> dict, IHeap<Integer, Integer> heap) throws MyException {
        switch (operation){
            case EQ:
                if(e1.eval(dict, heap) == e2.eval(dict, heap))
                    return 1;
                return 0;
            case NE:
                if(e1.eval(dict, heap) != e2.eval(dict, heap))
                    return 1;
                return 0;
            case LT:
                if(e1.eval(dict, heap) < e2.eval(dict, heap))
                    return 1;
                return 0;
            case LE:
                if(e1.eval(dict, heap) <= e2.eval(dict, heap))
                    return 1;
                return 0;
            case GT:
                if(e1.eval(dict, heap) > e2.eval(dict, heap))
                    return 1;
                return 0;
            case GE:
                if(e1.eval(dict, heap) >= e2.eval(dict, heap))
                    return 1;
                return 0;
        }
        throw new MyException("Operation not valid");
    }

    @Override
    public String toString() {
        return e1.toString() + operation + e2.toString();
    }
}
