package servlets;

import database.DBHelper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/VotePhoto")
public class VotePhoto extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String url = request.getParameter("url");
        String username = (String) request.getSession().getAttribute("currentUser");

        if (DBHelper.hasVote(username, url)){
            out.println("You have already voted this photo / is your photo!");
            out.println("<a href=\"index.jsp\">Home</a>");
        }
        else{
            request.getSession().setAttribute("url", url);
            out.println("<form action=\"VoteProcess\" method=\"post\">\n" +
                    "Mark for selected photo: <input type=\"number\" name=\"mark\" value=\"10\"><br>\n" +
                    "<input type=\"submit\" value=\"Submit\">\n" +
                    "</form>\n");
        }
        out.close();
    }

}