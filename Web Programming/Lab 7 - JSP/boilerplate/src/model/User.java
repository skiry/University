package model;

public class User {
    public Integer ID;
    public String Username;
    public String Password;
    public Integer Role;

    public User(Integer id, String username, String password, Integer Role) {
        this.ID = id;
        this.Username = username;
        this.Password = password;
        this.Role = Role;
    }
}
