package Model.DataStructures;

public class MyException extends Exception {
    public MyException(String message){
        super(message);
    }
    public MyException(Exception e) { super(e); }
}
