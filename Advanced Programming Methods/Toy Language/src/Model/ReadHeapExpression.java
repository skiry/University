package Model;

//returns the value associated to the key from heap which is
// the value associated to the id from the Symbol Table given as parameter
//error if id not found
public class ReadHeapExpression extends Expression {
    private String id;

    public ReadHeapExpression(String id){
        this.id = id;
    }

    @Override
    int eval(IDictionary<String, Integer> dict, IHeap<Integer, Integer> heap) throws MyException{

        if(!dict.containsKey(id))
            throw new MyException("Variable not in symbol table!");
        if(!heap.containsKey(dict.get(id)))
            throw new MyException("Variable not in the heap!");
        return heap.get(dict.get(id));
    }

    @Override
    public String toString() {
        return "rH(" + id + ")";
    }
}
