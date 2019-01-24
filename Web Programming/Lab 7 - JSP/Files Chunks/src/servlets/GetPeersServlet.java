package servlets;

import database.DBHelper;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/GetPeersServlet")
public class GetPeersServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        int t = Integer.parseInt(request.getParameter("t"));
        List<Integer> selects = new ArrayList<>();

        for(int i = 0; i < t; ++i) {
            selects.add(Integer.parseInt(request.getParameter("s" + i)));
        }
        System.out.println(selects);
        List<Integer> chunks = (List<Integer>) request.getSession().getAttribute("chunks");
        int cnt = 0;
        for(Integer chunk : chunks) {
            out.write(chunk + " is downloaded by " + selects.get(cnt++));
        }

        out.close();
    }

}
