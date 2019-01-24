<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 5/28/2019
  Time: 11:22 PM
  To change this template use File | Settings | File Templates.

  State information (between web requests) is always stored in a database;
  you may store some state information in cookies/session objects.
  Write a web application which allows users to upload pictures.
  Each user sees the pictures of all users and he/she can assign votes (natural numbers)
  for other users' pictures (not for his own pictures).
  If a picture gets votes from several users, these votes are added.
  The application then displays the top N pictures and the corresponding authors of these pictures,
  based on the number of votes; the number N should be chosen by the user.
  Each user must identify himself prior to using the application.

--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <title>Photo Contest</title>
    <style>
      form, a {
        margin-left: auto;
        margin-right: auto;
        width: 400px;
      }
    </style>
  </head>
  <body>
  <form>Hello, World!
  </form>
  <% if(request.getSession().getAttribute("currentUser") == null) { %>
  <form action="LoginServlet" method="post">
    Name:<input type="text" name="username"/><br/><br/>
    Password:<input type="password" name="userpass"/><br/><br/>

    <input type="submit" value="login"/>

  </form>
  <% } else { %>
  <a href="uploadFile.jsp">Upload a photo</a>
  <a href="displayImages.jsp">View photos</a>
  <form action="topImages.jsp" method="post">
    <input type="number" name="n" value="2">
    <input type="submit" value="Top Photos!">
  </form>
  <form action="LogoutServlet" method="post">
    <button type="submit" formmethod="post">Logout, <%= request.getSession().getAttribute("currentUser") %>! </button>
  </form>
  <% } %>
  </body>
</html>
