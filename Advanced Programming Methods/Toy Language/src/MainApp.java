import Controller.Controller;
import Model.DataStructures.*;
import Model.Expressions.*;
import Model.Statements.*;
import Repository.IRepository;
import Repository.MyRepository;
import UI.Menu.ExitCommand;
import UI.Menu.ProgramState;
import UI.Menu.RunExample;
import UI.Menu.TextMenu;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.*;

import static Model.DataStructures.BooleanSign.*;

//create each statement an add to an array of statements
//for each statement, create the structure that it needs, together with
//the program state, repository and controller and add it to commands menu
public class MainApp {
    public static void main(String[] args) throws IOException {
        int statementsCounter = 11;

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

        IStatement ex6 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(10)),
                new CompoundStatement(new NewStatement("v",new ConstantExpression(20)),
                        new CompoundStatement(new NewStatement("a",new ConstantExpression(22)),
                            new PrintStatement(new VariableExpression("v")))));
        ex.add(ex6);

        IStatement ex7 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(10)),
                new CompoundStatement(new NewStatement("v",new ConstantExpression(20)),
                        new CompoundStatement(new NewStatement("a",new ConstantExpression(22)),
                                new CompoundStatement(new PrintStatement(new ArithmeticExpression('+',new ConstantExpression(100),new ReadHeapExpression("v"))),
                                        new PrintStatement(new ArithmeticExpression('+',new ConstantExpression(100),new ReadHeapExpression("a")))))));
        ex.add(ex7);

        IStatement ex8 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(10)),
                new CompoundStatement(new NewStatement("v",new ConstantExpression(20)),
                        new CompoundStatement(new NewStatement("a",new ConstantExpression(22)),
                                new CompoundStatement(new WriteHeapStatement("a",new ConstantExpression(30)),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("a")),
                                            new PrintStatement(new ReadHeapExpression("a")))))));
        ex.add(ex8);

        IStatement ex9 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(10)),
                new CompoundStatement(new NewStatement("v",new ConstantExpression(20)),
                        new CompoundStatement(new NewStatement("a",new ConstantExpression(22)),
                                new CompoundStatement(new WriteHeapStatement("a",new ConstantExpression(30)),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("a")),
                                                new CompoundStatement(new PrintStatement(new ReadHeapExpression("a")),
                                                        new AssignmentStatement("a",new ConstantExpression(0))))))));
        ex.add(ex9);

        IStatement ex10 = new PrintStatement(new ArithmeticExpression('+', new ConstantExpression(10), new BooleanExpression(LT,new ConstantExpression(2),
                new ConstantExpression(6))));
        ex.add(ex10);

        IStatement ex11 = new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(6)),
                new CompoundStatement(new WhileStatement(new ArithmeticExpression('-',new VariableExpression("v"), new ConstantExpression(4)),
                        new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                new AssignmentStatement("v",new ArithmeticExpression('-',new VariableExpression("v"),new ConstantExpression(1))))),
                        new PrintStatement(new VariableExpression("v"))));
        ex.add(ex11);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0","Exit"));

        for(int i = 0; i < statementsCounter; ++i){
            IStack<IStatement> exeStack = new MyStack<>();
            IDictionary<String, Integer> symTable = new MyDictionary<>();
            IList<Integer> out = new MyList<>();
            IDictionary<Integer, Pair<String, BufferedReader>> fileTable = new MyFileTable<>();
            IHeap<Integer, Integer> heap = new MyHeap<>();

            ProgramState prg = new ProgramState(exeStack, symTable, out, ex.get(i), fileTable, heap);
            IRepository repo = new MyRepository(prg, "log"+Integer.toString(i+1)+".txt");
            Controller ctrl = new Controller(repo);

            menu.addCommand(new RunExample(Integer.toString(i+1),ex.get(i).toString(),ctrl));
        }
        menu.show();
    }

}
