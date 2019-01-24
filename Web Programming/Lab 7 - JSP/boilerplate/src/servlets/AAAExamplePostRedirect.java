/*
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

@WebServlet("/NAME")
public class NAME extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        //int id = Integer.parseInt(request.getParameter("id"));
        //String[] titles = request.getParameterValues("title[]");
        //String n=request.getParameter("username");

        DBHelper.connect();

        //FUNC EXECUTION
        for (int i = 0; i < titles.length; ++i){
            try {
                DBHelper.addContent(titles[i], descriptions[i], urls[i], (String)(request.getSession().getAttribute("currentUser")));
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        //UNTIL HERE

        RequestDispatcher rd = request.getRequestDispatcher("addContent.jsp");

        //FORWARD
        rd.forward(request,response);

        //INCLUDE, BESIDES ALL EXISTING CODE - getDispatcher of caller
        rd.include(request,response);

        out.close();
    }

}
*/
