using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.UI
{
    //option 0 selected. exit program.
    public class ExitCommand : Command {
        public ExitCommand(string key, string description) : base(key, description)
        {
        }
        public override void execute()
        {
            Environment.Exit(0);
        }
    }
}
