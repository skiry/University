package database;

import model.User;
import java.sql.*;
import java.util.*;

public class DBHelper {
    private static Statement statement;
    private static Connection conn;
    private static int maxId = -1;

    public DBHelper() {
    }

    public static void connect() {
        try {
            Class.forName("org.postgresql.Driver");
            conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/photoapp", "postgres", "ionut");
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
            String sql = "select * from users where name=? and password=?";
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1, username);
            ps.setString(2, password);
            rs = ps.executeQuery();

            if (rs.next()) {
                u = new User(rs.getInt("id"), rs.getString("name"), rs.getString("password"));
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

    public static void addPhoto(String username, String url) throws SQLException {
        ResultSet rs;
        if (maxId == -1) {
            maxId = 0;
            try {
                String sql = "select max(id) from photos";
                rs = statement.executeQuery(sql);

                if (rs.next()) {
                    maxId = rs.getInt(1);
                    System.err.println("Max is : " + maxId);
                }
                rs.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        maxId += 1;
        String sql = "insert into photos values(?,?, ?)";
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setInt(1, maxId);
        ps.setString(2, username);
        ps.setString(3, url);
        ps.executeUpdate();
    }

    public static List<String> getPhotos() {
        ResultSet rs;
        List<String> result = new ArrayList<>();
        try {
            String sql = "select * from photos";
            rs = statement.executeQuery(sql);

            while (rs.next()) {
                result.add(rs.getString("url"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return result;
    }

    public static boolean hasVote(String username, String url) {
        ResultSet rs;
        try {
            String sql = "select * from photos where url=?";
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1, url);
            rs = ps.executeQuery();

            if (rs.next()) {
                System.err.println(rs.getString("username") + " 1 " + username);
                if (rs.getString("username").equals(username)) {
                    System.err.println(true);
                    rs.close();
                    return true;
                }
            }

            sql = "select * from votes where url=?";
            PreparedStatement ps2 = conn.prepareStatement(sql);
            ps2.setString(1, url);
            rs = ps2.executeQuery();

            while(rs.next()){
                System.err.println(rs.getString("username") + " 2 " + username);
                if(rs.getString("username").equals(username)){
                    System.err.println(true);
                    rs.close();
                    return true;
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void addVote(String url, String user, Integer mark) {
        ResultSet rs;
        String sql = "insert into votes values(?,?, ?)";
        try {
        PreparedStatement ps = conn.prepareStatement(sql);
        ps.setString(1, user);
        ps.setString(2, url);
        ps.setInt(3, mark);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static List<String> getTopPhotos(Integer n) {
        HashMap<String, List<Integer>> hm = new HashMap<>();
        HashMap<String, Integer> gradedPhotos = new HashMap<>();
        ArrayList<Integer> sortedGrades = new ArrayList<>();
        ArrayList<String> takenPhotos = new ArrayList<>();

        ResultSet rs;
        try {
            String sql = "select * from votes";
            rs = statement.executeQuery(sql);

            while (rs.next()) {
                List<Integer> curr = hm.get(rs.getString("url"));
                if(curr == null){
                    ArrayList<Integer> newList = new ArrayList<>();
                    newList.add(rs.getInt("mark"));
                    hm.put(rs.getString("url"), newList);
                }
                else{
                    curr.add(rs.getInt("mark"));
                    hm.put(rs.getString("url"), curr);
                }
            }
            for(String url : hm.keySet()){
                Double nr = hm.get(url).stream().mapToInt(val->val).average().getAsDouble();
                gradedPhotos.put(url, nr.intValue());
                sortedGrades.add(nr.intValue());
            }
            System.err.println(gradedPhotos);
            System.err.println(sortedGrades);
            Collections.sort(sortedGrades);
            Collections.reverse(sortedGrades);
            System.err.println(sortedGrades);
            for(int i = 0; i < sortedGrades.size() && i < n; ++i)
            {
                boolean good = true;
                for(String url : gradedPhotos.keySet())
                {
                    if(good) {
                        if (gradedPhotos.get(url).equals(sortedGrades.get(i)) && !takenPhotos.contains(url)) {
                            takenPhotos.add(url);
                            good = false;
                        }
                    }
                }
            }
            System.err.println(takenPhotos);
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return takenPhotos;
    }
}
