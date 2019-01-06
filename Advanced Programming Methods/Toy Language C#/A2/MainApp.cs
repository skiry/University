using System;
using System.Collections.Generic;
using A2.Model;
using A2.Model.Data_Structures;
using A2.Model.Statements;
using A2.Model.Expressions;
using A2.UI;
using A2.Repository;
using System.IO;

namespace A2
{
    class MainApp
    {
        static void Main(string[] args)
        {
            int statementsCounter = 5;

            List<IStatement> ex = new List<IStatement>();

            IStatement ex1 = new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(2)),
                                new PrintStatement(new VariableExpression("v")));
            ex.Add(ex1);

            IStatement ex2 = new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression('+', new ConstantExpression(2), new ArithmeticExpression('*', new ConstantExpression(3), new ConstantExpression(5)))), new CompoundStatement(new AssignmentStatement("b", new ArithmeticExpression('+', new VariableExpression("a"), new ConstantExpression(1))), new PrintStatement(new VariableExpression("b"))));
            ex.Add(ex2);

            IStatement ex3 = new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression('-', new ConstantExpression(2), new ConstantExpression(2))), new CompoundStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ConstantExpression(2)), new AssignmentStatement("v", new ConstantExpression(3))), new PrintStatement(new VariableExpression("v"))));
            ex.Add(ex3);

            IStatement ex4 = new CompoundStatement(new openRFileStatement("var_f", "test.in"),
                    new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"),
                            new CompoundStatement(new PrintStatement(new VariableExpression("var_c")),
                                    new CompoundStatement(new IfStatement(new VariableExpression("var_c"), new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"), new PrintStatement(new VariableExpression("var_c"))), new PrintStatement(new ConstantExpression(0))),
                                            new closeRFileStatement(new VariableExpression("var_f"))))));
            ex.Add(ex4);

            IStatement ex5 = new CompoundStatement(new openRFileStatement("var_f", "test.in"),
                        new CompoundStatement(new readRFileStatement(new VariableExpression("var_f+2"), "var_c"),
                                new CompoundStatement(new PrintStatement(new VariableExpression("var_c")),
                                        new CompoundStatement(new IfStatement(new VariableExpression("var_c"), new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"), new PrintStatement(new VariableExpression("var_c"))), new PrintStatement(new ConstantExpression(0))),
                                                new closeRFileStatement(new VariableExpression("var_f"))))));
            ex.Add(ex5);

            TextMenu menu = new TextMenu();
            menu.addCommand(new ExitCommand("0", "Exit"));

            for (int i = 0; i < statementsCounter; ++i)
            {
                IStack<IStatement> exeStack = new MyStack<IStatement>();
                Model.Data_Structures.IDictionary<string, int> symTable = new MyDictionary<string, int>();
                Model.Data_Structures.IList<int> outList = new MyList<int>();
                Model.Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> fileTable = 
                    new MyFileTable<int, KeyValuePair<string, StreamReader>>();
                ProgramState prg = new ProgramState(exeStack, symTable, outList, fileTable, ex[i]);
                IRepository repo = new MyRepository(prg, "log" + (i + 1).ToString() + ".txt");
                Controller.Controller ctrl = new Controller.Controller(repo);

                menu.addCommand(new RunExample((i + 1).ToString(), ex[i].ToString(), ctrl));
            }
            menu.show();
        }
    }
}
