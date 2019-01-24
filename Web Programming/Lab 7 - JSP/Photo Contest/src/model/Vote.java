package model;

import java.util.stream.StreamSupport;

public class Vote {
    private String username;
    private String url;
    private Integer mark;

    public Vote(String username, String url, Integer mark) {
        this.username = username;
        this.url = url;
        this.mark = mark;
    }

    public String getUser_id() {
        return username;
    }

    public void setUser_id(String username) {
        this.username = username;
    }

    public String getPhoto_id() {
        return url;
    }

    public void setPhoto_id(String url) {
        this.url = url;
    }

    public Integer getMark() {
        return mark;
    }

    public void setMark(Integer mark) {
        this.mark = mark;
    }
}
