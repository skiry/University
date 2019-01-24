package model;

public class User {
    public Integer ID;
    public String User;
    public String Password;
    public Integer Role;

    public User(Integer id, String username, String password, Integer Role) {
        this.ID = id;
        this.User = username;
        this.Password = password;
        this.Role = Role;
    }
}
