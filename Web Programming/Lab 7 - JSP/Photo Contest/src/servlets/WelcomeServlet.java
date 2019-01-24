package servlets;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/WelcomeServlet")
public class WelcomeServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String n=request.getParameter("username");
        out.println("Successfully logged in!");
        out.println("Welcome "+n);
        out.println("<a href=\"index.jsp\">Home</a>");
        out.println("<a href=\"uploadFile.jsp\">Upload a photo</a>");
        out.close();
    }

}
