/*
package servlets;

import database.DBHelper;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet("/NAME")
public class NAME extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        //int id = Integer.parseInt(request.getParameter("id"));
        //String[] titles = request.getParameterValues("title[]");
        //String n=request.getParameter("username");

        DBHelper.connect();

        int cnt = 0;
        try {
            for (SOMETHING c : DBHelper.FUNC()){
                out.write("<div id=\"div" + cnt++ + "\">" + c.Title + "</div>");
            }
            out.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
*/
