package servlets;

import database.DBHelper;
import model.Content;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet("/DeleteContentServlet")
public class DeleteContentServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        int id = Integer.parseInt(request.getParameter("id"));

        DBHelper.connect();
        try {
            DBHelper.deleteContent(id);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
