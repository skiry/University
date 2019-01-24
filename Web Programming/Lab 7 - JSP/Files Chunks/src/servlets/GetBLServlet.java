package servlets;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

@WebServlet("/GetBLServlet")
public class GetBLServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        List<String> bl = (List<String>) request.getSession().getAttribute("blackList");

        for (String s : bl){
            out.write("<li>" + s + "</li>");
        }
        out.close();
    }

}
