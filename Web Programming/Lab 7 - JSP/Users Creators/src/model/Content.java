package model;

import java.util.Date;

public class Content {
    public Integer ID;
    public Date Date;
    public String Title;
    public String Description;
    public String URL;
    public Integer UserID;

    public Content(Integer ID, java.util.Date date, String title, String description, String URL, Integer userID) {
        this.ID = ID;
        Date = date;
        Title = title;
        Description = description;
        this.URL = URL;
        UserID = userID;
    }
}
