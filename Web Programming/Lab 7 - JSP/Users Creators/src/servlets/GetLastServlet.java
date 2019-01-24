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

@WebServlet("/GetLastServlet")
public class GetLastServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        DBHelper.connect();
        int cnt = 0;
        try {
            for (Content c : DBHelper.getLastContents()){
                out.write("<div id=\"div" + cnt++ + "\">" + c.Title + "</div>");
            }
            out.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
