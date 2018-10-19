package Model;

public class Complex {
    private double real, imag;
    public Complex(double a, double b){
        real = a;
        imag = b;
    }
    void aduna(Complex c){
        real += c.real;
        imag += c.imag;
    }
    Complex aduna(Complex c, int x){
        real += c.real;
        imag += c.imag;

        return this;
    }

}
