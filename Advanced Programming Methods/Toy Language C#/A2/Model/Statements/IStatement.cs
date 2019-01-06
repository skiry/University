using A2.UI;
using System;

namespace A2.Model.Statements
{
    public interface IStatement
    {
        string ToString();
        ProgramState execute(ProgramState state);
    }
}
