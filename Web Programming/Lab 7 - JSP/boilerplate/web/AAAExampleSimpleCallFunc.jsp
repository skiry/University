<%@ page import="java.util.List" %>
<%@ page import="database.DBHelper" %>
<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 6/17/2019
  Time: 3:43 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>TITLE</title>
</head>
<body>
<a href=index.jsp>Home</a>

<div id="imagelist">
    <%
        List<String> photoUrls = DBHelper.getPhotos();
        for(String url : photoUrls) {
            System.err.println(url);
            String redirectUrl = "VotePhoto?url=" + url; %>
    <a href=<%= redirectUrl %>><img alt="Image not loaded yet" src= <%= url %> ></a>
    <% } %>
</div>
</body>
</html>
