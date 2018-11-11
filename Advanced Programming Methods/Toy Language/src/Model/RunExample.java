package Model;

import Controller.Controller;

//run all steps from the given controller's statement
public class RunExample extends Command {
    private Controller ctrl;

    public RunExample(String key, String description, Controller ctrl) {
        super(key, description);
        this.ctrl = ctrl;
    }

    @Override
    public void execute() {
        try{
            ctrl.allSteps();
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
}
