package servlets;

import database.DBHelper;
import model.User;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.swing.event.InternalFrameEvent;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Optional;

@WebServlet("/VoteProcess")
public class VoteProcess extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {

        response.setContentType("text/html");

        String url = (String) request.getSession().getAttribute("url");
        String user = (String) request.getSession().getAttribute("currentUser");
        String mark = request.getParameter("mark");
        System.err.println("given mark = " + mark);

        DBHelper.addVote(url, user, Integer.parseInt(mark));

        RequestDispatcher rd=request.getRequestDispatcher("displayImages.jsp");
        rd.forward(request,response);
    }

}
