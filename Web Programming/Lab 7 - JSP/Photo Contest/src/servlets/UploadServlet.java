package servlets;
import java.io.*;
import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import database.DBHelper;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

@WebServlet("/UploadServlet")
public class UploadServlet extends HttpServlet {

    private String filePath;
    boolean uploaded = true;

    public void init( ){
        // Get the file location where it would be stored.
        filePath = getServletContext().getInitParameter("file-upload");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws java.io.IOException {

        // Check that we have a file upload request
        boolean isMultipart = ServletFileUpload.isMultipartContent(request);
        response.setContentType("text/html");
        java.io.PrintWriter out = response.getWriter( );

        if( !isMultipart) {
            printIntro(out);
            out.println("<p>No file uploaded</p>");
            out.println("</body>");
            out.println("</html>");
            return;
        }

        DiskFileItemFactory factory = new DiskFileItemFactory();

        // maximum size that will be stored in memory
        int maxMemSize = 4 * 1024;
        factory.setSizeThreshold(maxMemSize);

        // Location to save data that is larger than maxMemSize.
        factory.setRepository(new File("C:\\"));

        // Create a new file upload handler
        ServletFileUpload upload = new ServletFileUpload(factory);

        // maximum file size to be uploaded.
        int maxFileSize = 50 * 1024 * 20;
        upload.setSizeMax(maxFileSize);

        try {
            // Parse the request to get file items.
            List fileItems = upload.parseRequest(request);

            // Process the uploaded file items
            Iterator i = fileItems.iterator();

            printIntro(out);

            while ( i.hasNext () ) {
                FileItem fi = (FileItem)i.next();
                if ( !fi.isFormField () ) {
                    // Get the uploaded file parameters
                    String fieldName = fi.getFieldName();
                    String fileName = fi.getName();
                    String contentType = fi.getContentType();
                    boolean isInMemory = fi.isInMemory();
                    long sizeInBytes = fi.getSize();

                    // Write the file
                    File file;
                    if( fileName.lastIndexOf("\\") >= 0 ) {
                        file = new File( filePath + fileName.substring( fileName.lastIndexOf("\\"))) ;
                    } else {
                        file = new File( filePath + fileName.substring(fileName.lastIndexOf("\\")+1)) ;
                    }
                    fi.write(file) ;
                    DBHelper.addPhoto((String) request.getSession().getAttribute("currentUser"), fileName);
                    uploaded = true;
                    out.println("Uploaded Filename: " + fileName + "<br>");
                }
            }
            out.println("</body>");
            out.println("</html>");
        } catch(Exception ex) {
            System.out.println(ex);
            ex.printStackTrace();
            out.println(ex);
            out.println("<a href=\"uploadFile.jsp\">Try again</a>");
            uploaded = false;
        }
        if(uploaded) {
            out.println("Photo uploaded successfully!!!");
            out.println("<a href=\"index.jsp\">Home</a>");
        }
    }

    private void printIntro(PrintWriter out) {
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Servlet upload</title>");
        out.println("</head>");
        out.println("<body>");
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException {

        throw new ServletException("GET method used with " +
                getClass( ).getName( )+": POST method required.");
    }
}