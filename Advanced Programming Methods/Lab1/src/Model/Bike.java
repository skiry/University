package Model;

public class Bike implements IAutomobile {
    private String model;
    private boolean trainingWheel;
    private String colour;

    public Bike(String model, boolean trainingWheel, String colour){
        this.model = model;
        this.trainingWheel = trainingWheel;
        this.colour = colour;
    }

    public String toString(){
        if(trainingWheel)
            return model + " has helper wheels and colour " + colour;
        return model + " hasn't helper wheels and has colour " + colour;
    }

    @Override
    public String getColour() {
        return colour;
    }
}
