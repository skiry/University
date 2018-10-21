package Model;

public class VariableExpression extends Expression {
    private String id;

    public VariableExpression(String id){
        this.id = id;
    }

    @Override
    int eval(IDictionary<String, Integer> dict) throws MyException{
        if(!dict.containsKey(id))
            throw new MyException("Variable not in symbol table!");
        return dict.get(id);
    }

    @Override
    public String toString() {
        return id;
    }
}
