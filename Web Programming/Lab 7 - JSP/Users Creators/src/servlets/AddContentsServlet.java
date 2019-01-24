package servlets;


import database.DBHelper;
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

@WebServlet("/AddContentsServlet")
public class AddContentsServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String[] titles = request.getParameterValues("title[]");
        String[] descriptions = request.getParameterValues("description[]");
        String[] urls = request.getParameterValues("url[]");

        DBHelper.connect();

        for (int i = 0; i < titles.length; ++i){
            try {
                DBHelper.addContent(titles[i], descriptions[i], urls[i], (String)(request.getSession().getAttribute("currentUser")));
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        RequestDispatcher rd = request.getRequestDispatcher("addContent.jsp");
        rd.forward(request,response);
        out.close();
    }

}
