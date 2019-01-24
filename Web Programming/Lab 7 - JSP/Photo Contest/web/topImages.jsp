<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 5/29/2019
  Time: 6:31 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="java.util.List" %>
<%@ page import="database.DBHelper" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Top <%= request.getParameter("n") %> images</title>
    <style>
        img {
            width: 250px;
            height: 350px;
        }

        #imagelist {
            font-size: 0;
            width: 1200px;
            margin: 0 auto;
        }
        #imagelist img {
            margin: 2px;
            border: 4px solid black;
            display: inline-block;
            border-radius: 10px;
        }

        #imagelist img:hover {
            border-color: white;
        }
    </style>
</head>
<body>C:\Users\Skiry\Documents\Faculty\Sem2\Web\Lab 7 - JSP\out\artifacts\PhotoContest_war_exploded
<a href=index.jsp>Home</a>
<div id="imagelist">
    <%
        List<String> photoUrls = DBHelper.getTopPhotos(Integer.parseInt(request.getParameter("n")));
        for(String url : photoUrls) {
            System.err.println(url);
            String redirectUrl = "VotePhoto?url=" + url; %>
    <a href=<%= redirectUrl %>><img alt="Image not loaded yet" src= <%= url %> ></a>
    <% } %>
</div>
</body>
</html>
