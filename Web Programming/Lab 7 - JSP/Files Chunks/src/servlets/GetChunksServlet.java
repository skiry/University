package servlets;

import database.DBHelper;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

@WebServlet("/GetChunksServlet")
public class GetChunksServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        int id = Integer.parseInt(request.getParameter("q"));
        System.out.println(id);

        DBHelper.connect();
        List<Integer> chunks = DBHelper.getChunks(id);
        request.getSession().setAttribute("selects", chunks.size());
        request.getSession().setAttribute("chunks", chunks);
        int cnt = 0;
        for(Integer chunk : chunks) {
            List<String> peers = DBHelper.getPeers(chunk, (List<String>) request.getSession().getAttribute("blackList"));
            out.write("<li>");
            out.write("<select id=\"sel" + cnt++ + "\">");
            for(String peer : peers) {
                out.write("<option value=\"" + peer + "\">" + peer + "</option>");
            }
            out.write("</select>");
            out.write("</li>");
        }
        System.out.println(request.getSession().getAttribute("selects"));
        out.write("<button onclick=\"asschk()\">Assign chunks</button>");
        out.close();
    }

}
