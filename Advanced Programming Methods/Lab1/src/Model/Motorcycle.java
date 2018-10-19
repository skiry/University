package Model;

public class Motorcycle implements IAutomobile {
    private String model;
    private int noOfWheels;
    private String colour;

    public Motorcycle(String model, int noOfWheels, String colour){
        this.model = model;
        this.noOfWheels = noOfWheels;
        this.colour = colour;
    }

    public String toString(){
        return model + " has " +
                String.valueOf(noOfWheels) + " wheels and has colour " + colour;
    }

    @Override
    public String getColour() {
        return colour;
    }
}
