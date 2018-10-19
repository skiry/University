package Model;

public class Cars implements IAutomobile {
    private String model;
    private int year;
    private String colour;

    public Cars(String model, int year, String colour){
        this.model = model;
        this.year = year;
        this.colour = colour;
    }

    public String toString(){
        return model + " from year " +
                String.valueOf(year) + " has colour " + colour;
    }

    @Override
    public String getColour() {
        return colour;
    }
}