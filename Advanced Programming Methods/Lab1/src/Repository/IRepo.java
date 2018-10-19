package Repository;

import Model.IAutomobile;

public interface IRepo {
    void add(IAutomobile a);
    void remove(int id);
    IAutomobile[] filter(String s);
}
