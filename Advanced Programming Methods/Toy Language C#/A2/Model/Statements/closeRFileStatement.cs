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
    //search for the expression's result in the File Table
    //if not found or expression not evaluated, throw error
    //otherwise, close the file from the associated bufferedReader and remove the entry from the File Table
    public class closeRFileStatement : IStatement {
        private Expression expFileId;

        public closeRFileStatement(Expression expFileId)
        {
            this.expFileId = expFileId;
        }
        public ProgramState execute(ProgramState state) {
            IStack<IStatement> stk = state.getExeStack();
            Data_Structures.IFileTable<int, KeyValuePair<string, StreamReader>> fileTable = state.getFileTable();
            Data_Structures.IDictionary<string, int> symTbl = state.getSymTable();

            int result;
            try{
                result = expFileId.eval(symTbl);
            }
            catch(Exception e){
                throw new MyException("Error evaluating the expression" + e.Message);
            }
            Boolean exists = false;
            StreamReader myFile = null;

                foreach(int el in fileTable.keySet()){
                    if(el == result) {
                        exists = true;
                        myFile = fileTable.get(el).Value;
                    }
                }
                if( !exists ){
                    throw new MyException("Key not in File Table!");
                }
                else{
                    myFile.Close();
                    fileTable.remove(result);
                }
                return state;
            }

        public override string ToString()
        {
            string res = "closeRFile(";
            res += expFileId.ToString();
            res += ")";
            return res;
        }
    }
}
