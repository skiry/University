using A2.Model.Data_Structures;
using A2.Model.Statements;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.UI
{
    //Program State keeps a reference to all important structures together with their getters and setters
    public class ProgramState
    {
        private IStack<IStatement> exeStack;
        private Model.Data_Structures.IDictionary<string, int> symTable;
        private Model.Data_Structures.IList<int> outList;
        private Model.Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> fileTable;
        private IStatement originalProgram;

        public ProgramState(IStack<IStatement> exeStack,
                          Model.Data_Structures.IDictionary<string, int> symTable,
                          Model.Data_Structures.IList<int> outList,
                          Model.Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> fileTable,
                          IStatement originalProgram)
        {
            this.exeStack = exeStack;
            this.symTable = symTable;
            this.outList = outList;
            this.fileTable = fileTable;
            this.originalProgram = originalProgram;
            this.exeStack.push(originalProgram);
        }

        public IStack<IStatement> getExeStack()
        {

            return exeStack;
        }
        public Model.Data_Structures.IDictionary<string, int> getSymTable()
        {
            return symTable;
        }
        public Model.Data_Structures.IList<int> getOut()
        {

            return outList;
        }
        public Model.Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> getFileTable()
        {
            return fileTable;
        }
        IStatement getOriginalProgram()
        {

            return originalProgram;
        }

        void setExeStack(IStack<IStatement> exeStack)
        {
            this.exeStack = exeStack;
        }
        void setSymTable(Model.Data_Structures.IDictionary<string, int> symTable)
        {
            this.symTable = symTable;
        }
        void setOut(Model.Data_Structures.IList<int> outList)
        {

            this.outList = outList;
        }
        void setOriginalProgram(IStatement originalProgram)
        {

            this.originalProgram = originalProgram;
        }
        void setFileTable(Model.Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> fileTable)
        {
            this.fileTable = fileTable;
        }
    }

}
