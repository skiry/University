using System;
using System.Collections.Generic;
using A2.UI;
using A2.Model.Data_Structures;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace A2.Model.Statements
{
    //open the file fileName - if fileName already opened, throw exception -
    //otherwise, add <unique FD,pair<fileName, bufferedReadder>> pair to fileTable to keep evidence of opened files
    //also, to acces this file, add <varFileId, unique FD> pair to symbolTable
    public class openRFileStatement : IStatement {
        private String varFileId;
        private String fileName;
        private static int fileDescriptor = 1;

        public openRFileStatement(String varFileId, String fileName)
        {
            this.varFileId = varFileId;
            this.fileName = fileName;
        }
        public ProgramState execute(ProgramState state) {
            IStack<IStatement> stk = state.getExeStack();
            Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> fileTable = state.getFileTable();
            Data_Structures.IDictionary<string, int> symTbl = state.getSymTable();

            StreamReader myFile = null;

            foreach (KeyValuePair<string, StreamReader> el in fileTable.values()) {
                    if (el.Key == fileName) {
                        throw new MyException("File Name already in the File Table");
                    }
            }

            myFile = new StreamReader(fileName);
            fileTable.put(fileDescriptor, new KeyValuePair<string, StreamReader>(fileName, myFile));
            symTbl.put(varFileId, fileDescriptor++);

            return state;
        }

            public override string ToString()
        {
            string res = "openRFile(";
            res += varFileId;
            res += ",";
            res += fileName;
            res += ")";
            return res;
        }
    }
}
