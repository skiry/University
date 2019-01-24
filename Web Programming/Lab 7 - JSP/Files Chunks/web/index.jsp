<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 6/16/2019
  Time: 1:25 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <title>Login page</title>
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
  <input type="submit" value="login"/>
</form>
<% } else { %>

<a href="manageBL.jsp">Manage black list</a>
<a href="keywordSearch.jsp">Search files</a>

<form action="LogoutServlet" method="post">
  <button type="submit" formmethod="post">Logout, <%= request.getSession().getAttribute("currentUser") %>! </button>
</form>
<% } %>
</body>
</html>
