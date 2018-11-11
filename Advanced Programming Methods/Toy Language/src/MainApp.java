import Controller.Controller;
import Model.*;
import Repository.IRepository;
import Repository.MyRepository;
import UI.UI;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.*;

//create each statement an add to an array of statements
//for each statement, create the structure that it needs, together with
//the program state, repository and controller and add it to commands menu
public class MainApp {
    public static void main(String[] args) throws IOException {
        int statementsCounter = 5;

        ArrayList<IStatement> ex = new ArrayList<>();

        IStatement ex1 = new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(2)),
                            new PrintStatement(new VariableExpression("v")));
        ex.add(ex1);

        IStatement ex2 = new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression('+', new ConstantExpression(2), new ArithmeticExpression('*', new ConstantExpression(3), new ConstantExpression(5)))), new CompoundStatement(new AssignmentStatement("b", new ArithmeticExpression('+', new VariableExpression("a"), new ConstantExpression(1))), new PrintStatement(new VariableExpression("b"))));
        ex.add(ex2);

        IStatement ex3 = new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression('-', new ConstantExpression(2), new ConstantExpression(2))), new CompoundStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ConstantExpression(2)), new AssignmentStatement("v", new ConstantExpression(3))), new PrintStatement(new VariableExpression("v"))));
        ex.add(ex3);

        IStatement ex4 = new CompoundStatement(new openRFileStatement("var_f", "test.in"),
                    new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"),
                            new CompoundStatement(new PrintStatement(new VariableExpression("var_c")),
                                    new CompoundStatement(new IfStatement(new VariableExpression("var_c"), new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"), new PrintStatement(new VariableExpression("var_c"))), new PrintStatement(new ConstantExpression(0))),
                                            new closeRFileStatement(new VariableExpression("var_f"))))));
        ex.add(ex4);

        IStatement ex5 = new CompoundStatement(new openRFileStatement("var_f", "test.in"),
                    new CompoundStatement(new readRFileStatement(new VariableExpression("var_f+2"), "var_c"),
                            new CompoundStatement(new PrintStatement(new VariableExpression("var_c")),
                                    new CompoundStatement(new IfStatement(new VariableExpression("var_c"), new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"), new PrintStatement(new VariableExpression("var_c"))), new PrintStatement(new ConstantExpression(0))),
                                            new closeRFileStatement(new VariableExpression("var_f"))))));
        ex.add(ex5);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0","Exit"));

        for(int i = 0; i < statementsCounter; ++i){
            IStack<IStatement> exeStack = new MyStack<>();
            IDictionary<String, Integer> symTable = new MyDictionary<>();
            IList<Integer> out = new MyList<>();
            IDictionary<Integer, Pair<String, BufferedReader>> fileTable = new MyFileTable<>();

            ProgramState prg = new ProgramState(exeStack, symTable, out, ex.get(i), fileTable);
            IRepository repo = new MyRepository(prg, "log"+Integer.toString(i+1)+".txt");
            Controller ctrl = new Controller(repo);

            menu.addCommand(new RunExample(Integer.toString(i+1),ex.get(i).toString(),ctrl));
        }
        menu.show();
    }

}
