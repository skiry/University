using System;
using A2.UI;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace A2.Repository
{
    //repo is a list of program states. in reality, it adds only one repo.
    //first, Write nothing to file with no append - clear the file -
    //Write all the structures with append at every logExec step
    public class MyRepository : IRepository{
        private List<ProgramState> repo;
        private StreamWriter logFile;

        public MyRepository(ProgramState state, string path)
        {
            this.repo = new List<ProgramState>();
            this.repo.Add(state);
            StreamWriter clearFile = new StreamWriter(path, false);
            clearFile.Write("");
            clearFile.Close();
            this.logFile = new StreamWriter(path, true);
        }
        public void add(ProgramState s)
        {
            this.repo.Add(s);
        }
        public ProgramState getCurrentProgram()
        {
            return repo[repo.Count() - 1];
        }
        public void logProgramStateExec()
        {
            ProgramState cur = getCurrentProgram();
            logFile.Write(cur.getExeStack().ToString());
            logFile.WriteLine();
            logFile.WriteLine();
            logFile.Write(cur.getSymTable().ToString());
            logFile.WriteLine();
            logFile.WriteLine();
            logFile.Write(cur.getOut().ToString());
            logFile.WriteLine();
            logFile.WriteLine();
            //logFile.Write(cur.getFileTable().ToString());
            logFile.WriteLine();
            logFile.WriteLine();
            logFile.Write("-------------------------");
            logFile.WriteLine();

        }
        public void closeLogFile()
        {
            //Closing a previously closed stream has no effect
            this.logFile.Close();
        }
    }
}
