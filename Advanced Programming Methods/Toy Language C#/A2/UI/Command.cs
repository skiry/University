using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.UI
{
    public abstract class Command
    {
        private string key, description;

        protected Command(string key, string description)
        {
            this.key = key;
            this.description = description;
        }

        public abstract void execute();

        public string getKey()
        {
            return key;
        }

        public string getDescription()
        {
            return description;
        }
    }
}
