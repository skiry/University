import Controller.Ctrl;
import Model.Bike;
import Model.Cars;
import Model.IAutomobile;
import Model.Motorcycle;
import Repository.Repo;
import View.MyApp;

public class MainApp {
    public static void main(String[] args){
        Cars c = new Cars("Mercedes",2007,"red");
        Bike b = new Bike("Focus",true,"green");
        Motorcycle m = new Motorcycle("Yamaha",2,"red");

        Repo r = new Repo(3);
        try{
        r.add(c);
        r.add(b);
        r.add(m);}
        catch(RuntimeException e){
            System.out.println(e.getMessage());
        }
        Ctrl ctrl = new Ctrl(r);
        MyApp app = new MyApp(ctrl);
        for(IAutomobile e:app.filter("red"))
            System.out.println(e.toString());
        int x=2,y=4;
        app.interschimba(x,y);
        System.out.println(x);
        System.out.println(y);
    }
}
