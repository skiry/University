using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace A2.UI
{
    //hashmap that keeps value-command pairs
    public class TextMenu
    {
        private Dictionary<string, Command> commands;

        public TextMenu()
        {
            commands = new Dictionary<string, Command>();
        }

        public void addCommand(Command c)
        {
            commands.Add(c.getKey(), c);
        }

        private void printMenu()
        {
            foreach (Command com in this.commands.Values)
            {
                Console.WriteLine($"{com.getKey()}:{com.getDescription()}");
            }
        }

        public void show()
        {
            while (true)
            {
                printMenu();
                Console.Write("Input the option: ");
                String key = Console.ReadLine();
                Command com;
                commands.TryGetValue(key, out com);
                if (com == null)
                {
                    Console.WriteLine("Invalid Option");
                    continue;
                }
                com.execute();
            }
        }
    }
}
