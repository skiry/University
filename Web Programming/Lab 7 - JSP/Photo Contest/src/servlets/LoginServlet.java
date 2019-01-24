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
import java.util.Optional;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String n=request.getParameter("username");
        String p=request.getParameter("userpass");

        DBHelper.connect();
        Optional<User> user = DBHelper.authenticate(n, p);
        if (user.isPresent())
        {
            request.getSession().setAttribute("currentUser", user.get().getUsername());
            System.err.println("current user: " + request.getSession().getAttribute("currentUser"));
            RequestDispatcher rd=request.getRequestDispatcher("WelcomeServlet");
            rd.forward(request,response);
        }
        else{
            out.print("Username or password incorrect");
            RequestDispatcher rd=request.getRequestDispatcher("index.jsp");
            rd.include(request,response);
        }
        out.close();
    }

}
