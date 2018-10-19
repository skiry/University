package View;

import Controller.Ctrl;
import Model.IAutomobile;

public class MyApp {
    private Ctrl ctrl;

    public MyApp(Ctrl ctrl){
        this.ctrl = ctrl;
    }

    public void add(IAutomobile a){
        ctrl.add(a);
    }

    public void interschimba(int x, int y){
        int tmp = x;
        x=y;
        y=tmp;
    }

    public IAutomobile[] filter(String colour){
        return ctrl.filter(colour);
    }
}
