package servlets;

import database.DBHelper;
import model.Content;
import model.User;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

@WebServlet("/UpdateInfoServlet")
public class UpdateInfoServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        List<String> l = new ArrayList<>();
        l.add(request.getParameter("t1"));
        l.add(request.getParameter("t2"));
        l.add(request.getParameter("t3"));
        l.add(request.getParameter("t4"));

        DBHelper.connect();
        int cnt = 0;
        try {
            for (Content c : DBHelper.getLastContents()){
                if (!l.contains(c.Title) && cnt == 0){
                    System.out.println((l + c.Title));
                    cnt = 1;
                    out.write("New content was added!");
                }
            }
            out.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
