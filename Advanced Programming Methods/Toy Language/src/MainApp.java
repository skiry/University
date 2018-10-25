import Controller.Controller;
import Model.*;
import Repository.IRepository;
import Repository.MyRepository;
import UI.UI;

import java.util.HashSet;
import java.util.Set;

public class MainApp {
    public static void main(String[] args){

        IStack<IStatement> exeStack = new MyStack<>();
        IDictionary<String,Integer> symTable = new MyDictionary<>();
        IList<Integer> out = new MyList<>();
        IStatement ex1= new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(2)),
                new PrintStatement(new VariableExpression("v")));
        IStatement ex2 = new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression('+',new ConstantExpression(2),new ArithmeticExpression('*',new ConstantExpression(3), new ConstantExpression(5)))),  new CompoundStatement(new AssignmentStatement("b",new ArithmeticExpression('+',new VariableExpression("a"), new ConstantExpression(1))), new PrintStatement(new VariableExpression("b"))));
        IStatement ex3 = new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression('-',new ConstantExpression(2), new ConstantExpression(2))), new CompoundStatement(new IfStatement(new VariableExpression("a"),new AssignmentStatement("v",new ConstantExpression(2)), new AssignmentStatement("v", new ConstantExpression(3))), new PrintStatement(new VariableExpression("v"))));

        ProgramState prg = new ProgramState(exeStack, symTable, out, ex2);

        IRepository repo = new MyRepository(prg);
        Controller ctrl = new Controller(repo);
        UI ui = new UI(ctrl);
        ui.run();
    }

}
