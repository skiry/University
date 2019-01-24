package database;

import model.Content;
import model.User;

import java.sql.*;
import java.time.LocalDate;
import java.util.*;
import java.util.Date;

public class DBHelper {
    private static Statement statement;
    private static Connection conn;
    private static int maxId = -1;
    private static int userid = -1;

    public DBHelper() {
    }

    public static void connect() {
        try {
            Class.forName("org.postgresql.Driver");
            conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/userscreators", "postgres", "ionut");
            statement = conn.createStatement();
        } catch (Exception ex) {
            System.out.println("Connection error: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public static Optional<User> authenticate(String username, String password) {
        ResultSet rs;
        User u = null;
        System.out.println(username + " " + password);
        try {
            String sql = "select * from users where \"User\"=? and password=?";
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1, username);
            ps.setString(2, password);
            rs = ps.executeQuery();

            if (rs.next()) {
                u = new User(rs.getInt("ID"), rs.getString("User"),
                        rs.getString("Password"), rs.getInt("Role"));
                rs.close();
            } else {
                rs.close();
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(u);
    }

    public static void addContent(String title, String description, String url, String username) throws SQLException {
        ResultSet rs1;
        String sql = "select * from users where \"User\"=\'" + username + "\'";
        rs1 = statement.executeQuery(sql);

        if(rs1.next()){
            userid = rs1.getInt("ID");
        }
        System.out.println("received id: " + userid);

        ResultSet rs;
        String sql2 = "insert into content(date, title, description, url, userid) values(?,?,?,?,?)";
        try {
            PreparedStatement ps = conn.prepareStatement(sql2);
            ps.setDate(1, java.sql.Date.valueOf(LocalDate.now()));
            ps.setString(2, title);
            ps.setString(3, description);
            ps.setString(4, url);
            ps.setInt(5, userid);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static List<Content> getContents(String username) throws SQLException {
        ResultSet rs1;
        String stmt = "select * from users where \"User\"=\'" + username + "\'";
        rs1 = statement.executeQuery(stmt);

        if(rs1.next()){
            userid = rs1.getInt("ID");
        }

        ResultSet rs;
        String sql = "select * from content where userid=" + userid;
        rs = statement.executeQuery(sql);
        List<Content> result = new ArrayList<>();

        while(rs.next()) {
            System.out.println(rs.getString("Title"));
            result.add(new Content(rs.getInt("id"),
                    rs.getDate("date"),
                    rs.getString("title"),
                    rs.getString("description"),
                    rs.getString("url"),
                    rs.getInt("userid")));
        }
        System.out.println(result);
        return result;
    }

    public static void deleteContent(int id) throws SQLException {
        ResultSet rs;
        String sql2 = "delete from content where id=" + id;
        statement.executeUpdate(sql2);
    }

    public static List<Content> getLastContents() throws SQLException {
        ResultSet rs;
        String sql = "select * from content order by id desc limit 4";
        rs = statement.executeQuery(sql);
        List<Content> result = new ArrayList<>();

        while(rs.next()) {
            System.out.println(rs.getString("Title"));
            result.add(new Content(rs.getInt("id"),
                    rs.getDate("date"),
                    rs.getString("title"),
                    rs.getString("description"),
                    rs.getString("url"),
                    rs.getInt("userid")));
        }
        System.out.println(result);
        return result;
    }
}
