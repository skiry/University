using System;
using A2.Controller;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.UI
{
    //run all steps from the given controller's statement
    public class RunExample : Command {
        private Controller.Controller ctrl;

        public RunExample(string key, string description, Controller.Controller ctrl) : base(key, description)
        {
            this.ctrl = ctrl;
        }
        public override void execute()
        {
            try
            {
                ctrl.allSteps();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
