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
import java.util.List;

@WebServlet("/DeleteBLServlet")
public class DeleteBLServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");

        String username = request.getParameter("username");
        List<String> bl = (List<String>) request.getSession().getAttribute("blackList");

        if(bl.contains(username)) {
            bl.remove(username);
        }

        request.getSession().setAttribute("blackList", bl);


        RequestDispatcher rd = request.getRequestDispatcher("manageBL.jsp");

        rd.forward(request,response);

    }

}
