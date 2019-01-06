package UI.Menu;

//option 0 selected. exit program.
public class ExitCommand extends Command {
    public ExitCommand(String key, String description){
        super(key, description);
    }
    @Override
    public void execute() {
        System.exit(0);
    }
}
