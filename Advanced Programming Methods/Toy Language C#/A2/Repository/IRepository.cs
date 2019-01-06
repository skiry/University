using System;
using A2.UI;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.Repository
{
    public interface IRepository
    {
        void add(ProgramState s);
        ProgramState getCurrentProgram();
        void logProgramStateExec();
        void closeLogFile();
    }
}
