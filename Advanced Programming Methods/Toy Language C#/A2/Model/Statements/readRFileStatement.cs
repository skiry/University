using System;
using System.Collections.Generic;
using A2.UI;
using A2.Model.Data_Structures;
using A2.Model.Expressions;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace A2.Model.Statements
{
    //evaluate the expression to search for that value in the fileTable
    //if not found, throw error
    //otherwise, S = read a line from the associated bufferedReader
    //if read, add <varName, S> pair in the Symbol Table
    public class readRFileStatement : IStatement
    {
    private Expression expFileId;
    private string varName;

    public readRFileStatement(Expression expFileId, string varName)
    {
        this.expFileId = expFileId;
        this.varName = varName;
    }
    public ProgramState execute(ProgramState state) {
        IStack<IStatement> stk = state.getExeStack();
        Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> fileTable = state.getFileTable();
        Data_Structures.IDictionary<string, int> symTbl = state.getSymTable();

        int result = expFileId.eval(symTbl);
        Boolean exists = false;
        StreamReader myFile = null;

        foreach (int el in fileTable.keySet()){
            if(el == result) {
                exists = true;
                myFile = fileTable.get(el).Value;
            }
        }

        if( !exists ){
            throw new MyException("Key not in File Table!");
        }

        string read = myFile.ReadLine();
        if(read != null) {
                symTbl.put(varName, Convert.ToInt32(read));
        }
        else {
            symTbl.put(varName, 0);
        }
        return state;
    }

        public override string ToString()
        {
            string res = "readRFile(";
            res += expFileId.ToString();
            res += ",";
            res += varName;
            res += ")";
            return res;
        }
    }
}
