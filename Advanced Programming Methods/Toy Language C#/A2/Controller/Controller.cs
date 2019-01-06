using System;
using A2.Repository;
using A2.UI;
using A2.Model.Statements;
using A2.Model.Data_Structures;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Collections.Generic;

namespace A2.Controller
{
    //keeps a reference to the repository
    //oneStep calls execute() for the head of the Execution Stack
    //allSteps calls oneStep() until the Execution Stack is empty
    public class Controller
    {
        private IRepository repo;

        public Controller(IRepository repo)
        {
            this.repo = repo;
        }
        
        public ProgramState oneStep() {
            ProgramState state = repo.getCurrentProgram();
            IStack<IStatement> stk = state.getExeStack();

            Console.WriteLine(state.getExeStack());
            Console.WriteLine(state.getSymTable());
            Console.WriteLine(state.getOut());
            Console.WriteLine(state.getFileTable());

            if(stk.isEmpty()) {
                throw new MyException("Empty Execution Stack!!!");
        }
        IStatement current = stk.pop();
        Console.WriteLine("\n"+current.ToString()+"\n");

            return current.execute(state);
        }
        public void allSteps()
        {
            ProgramState prg = repo.getCurrentProgram();
            IStack<IStatement> stk = prg.getExeStack();
            Model.Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> fileTable = prg.getFileTable();

            try
            {
                while (!stk.isEmpty())
                {
                    oneStep();
                    repo.logProgramStateExec();
                }
                repo.closeLogFile();
                Console.WriteLine(prg.getExeStack());
                Console.WriteLine(prg.getSymTable());
                Console.WriteLine(prg.getOut());
                Console.WriteLine(prg.getFileTable());
            }
            catch (MyException exc)
            {
                Console.WriteLine(exc.Message);
            }
            finally
            {
                /*((MyFileTable<Integer, Pair<String, BufferedReader>>)fileTable).stream()
                        .forEach(s-> {
                    try
                    {
                        s.getValue().getSecond().close();
                    }
                    catch (IOException e)
                    {
                        e.printStackTrace();
                    }
                });*/
            }
        }
    }
}
