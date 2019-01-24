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
import java.util.Optional;

@WebServlet("/GetContentsServlet")
public class GetContentsServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        DBHelper.connect();
        try {
            for (Content c : DBHelper.getContents((String)request.getSession().getAttribute("currentUser"))){
                out.write("<option value=\"" + c.ID + "\"" + ">" + c.Title + "</option>");
            }
            out.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
