package UI;

import Controller.Controller;
import Model.DataStructures.MyException;

import java.io.IOException;

//before the TextMenu class there was the UI class that received a controller and ran according to a boolean all/one step(s)
public class UI {
    private Controller ctrl;

    public UI(Controller ctrl){
        this.ctrl = ctrl;
    }

    public void run(boolean flag) throws MyException, IOException {
        if(flag) {
            ctrl.allSteps();
        }
        else {
            ctrl.oneStep();
        }
    }
}
