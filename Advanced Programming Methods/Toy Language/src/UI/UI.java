package UI;

import Controller.Controller;
import Model.MyException;

import java.awt.desktop.SystemSleepEvent;

public class UI {
    private Controller ctrl;

    public UI(Controller ctrl){
        this.ctrl = ctrl;
    }

    public void run(){
        ctrl.allSteps();
    }
}
